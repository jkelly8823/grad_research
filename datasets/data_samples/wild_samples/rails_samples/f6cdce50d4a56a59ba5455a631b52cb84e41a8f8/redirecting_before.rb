# frozen_string_literal: true

module ActionController
  module Redirecting
    extend ActiveSupport::Concern

    include AbstractController::Logger
    include ActionController::UrlFor

    class UnsafeRedirectError < StandardError; end

    included do
      mattr_accessor :raise_on_open_redirects, default: false
    end

    # Redirects the browser to the target specified in +options+. This parameter can be any one of:
    #
    # * <tt>Hash</tt> - The URL will be generated by calling url_for with the +options+.
    # * <tt>Record</tt> - The URL will be generated by calling url_for with the +options+, which will reference a named URL for that record.
    # * <tt>String</tt> starting with <tt>protocol://</tt> (like <tt>http://</tt>) or a protocol relative reference (like <tt>//</tt>) - Is passed straight through as the target for redirection.
    # * <tt>String</tt> not containing a protocol - The current protocol and host is prepended to the string.
    # * <tt>Proc</tt> - A block that will be executed in the controller's context. Should return any option accepted by +redirect_to+.
    #
    # === Examples:
    #
    #   redirect_to action: "show", id: 5
    #   redirect_to @post
    #   redirect_to "http://www.rubyonrails.org"
    #   redirect_to "/images/screenshot.jpg"
    #   redirect_to posts_url
    #   redirect_to proc { edit_post_url(@post) }
    #
    # The redirection happens as a <tt>302 Found</tt> header unless otherwise specified using the <tt>:status</tt> option:
    #
    #   redirect_to post_url(@post), status: :found
    #   redirect_to action: 'atom', status: :moved_permanently
    #   redirect_to post_url(@post), status: 301
    #   redirect_to action: 'atom', status: 302
    #
    # The status code can either be a standard {HTTP Status code}[https://www.iana.org/assignments/http-status-codes] as an
    # integer, or a symbol representing the downcased, underscored and symbolized description.
    # Note that the status code must be a 3xx HTTP code, or redirection will not occur.
    #
    # If you are using XHR requests other than GET or POST and redirecting after the
    # request then some browsers will follow the redirect using the original request
    # method. This may lead to undesirable behavior such as a double DELETE. To work
    # around this you can return a <tt>303 See Other</tt> status code which will be
    # followed using a GET request.
    #
    #   redirect_to posts_url, status: :see_other
    #   redirect_to action: 'index', status: 303
    #
    # It is also possible to assign a flash message as part of the redirection. There are two special accessors for the commonly used flash names
    # +alert+ and +notice+ as well as a general purpose +flash+ bucket.
    #
    #   redirect_to post_url(@post), alert: "Watch it, mister!"
    #   redirect_to post_url(@post), status: :found, notice: "Pay attention to the road"
    #   redirect_to post_url(@post), status: 301, flash: { updated_post_id: @post.id }
    #   redirect_to({ action: 'atom' }, alert: "Something serious happened")
    #
    # Statements after +redirect_to+ in our controller get executed, so +redirect_to+ doesn't stop the execution of the function.
    # To terminate the execution of the function immediately after the +redirect_to+, use return.
    #
    #   redirect_to post_url(@post) and return
    #
    # === Open Redirect protection
    #
    # By default, Rails protects against redirecting to external hosts for your app's safety, so called open redirects.
    # Note: this was a new default in Rails 7.0, after upgrading opt-in by uncommenting the line with +raise_on_open_redirects+ in <tt>config/initializers/new_framework_defaults_7_0.rb</tt>
    #
    # Here #redirect_to automatically validates the potentially-unsafe URL:
    #
    #   redirect_to params[:redirect_url]
    #
    # Raises UnsafeRedirectError in the case of an unsafe redirect.
    #
    # To allow any external redirects pass <tt>allow_other_host: true</tt>, though using a user-provided param in that case is unsafe.
    #
    #   redirect_to "https://rubyonrails.org", allow_other_host: true
    #
    # See #url_from for more information on what an internal and safe URL is, or how to fall back to an alternate redirect URL in the unsafe case.
    def redirect_to(options = {}, response_options = {})
      raise ActionControllerError.new("Cannot redirect to nil!") unless options
      raise AbstractController::DoubleRenderError if response_body

      allow_other_host = response_options.delete(:allow_other_host) { _allow_other_host }

      self.status        = _extract_redirect_to_status(options, response_options)
      self.location      = _enforce_open_redirect_protection(_compute_redirect_to_location(request, options), allow_other_host: allow_other_host)
      self.response_body = ""
    end

    # Soft deprecated alias for #redirect_back_or_to where the +fallback_location+ location is supplied as a keyword argument instead
    # of the first positional argument.
    def redirect_back(fallback_location:, allow_other_host: _allow_other_host, **args)
      redirect_back_or_to fallback_location, allow_other_host: allow_other_host, **args
    end

    # Redirects the browser to the page that issued the request (the referrer)
    # if possible, otherwise redirects to the provided default fallback
    # location.
    #
    # The referrer information is pulled from the HTTP +Referer+ (sic) header on
    # the request. This is an optional header and its presence on the request is
    # subject to browser security settings and user preferences. If the request
    # is missing this header, the <tt>fallback_location</tt> will be used.
    #
    #   redirect_back_or_to({ action: "show", id: 5 })
    #   redirect_back_or_to @post
    #   redirect_back_or_to "http://www.rubyonrails.org"
    #   redirect_back_or_to "/images/screenshot.jpg"
    #   redirect_back_or_to posts_url
    #   redirect_back_or_to proc { edit_post_url(@post) }
    #   redirect_back_or_to '/', allow_other_host: false
    #
    # ==== Options
    # * <tt>:allow_other_host</tt> - Allow or disallow redirection to the host that is different to the current host, defaults to true.
    #
    # All other options that can be passed to #redirect_to are accepted as
    # options, and the behavior is identical.
    def redirect_back_or_to(fallback_location, allow_other_host: _allow_other_host, **options)
      if request.referer && (allow_other_host || _url_host_allowed?(request.referer))
        redirect_to request.referer, allow_other_host: allow_other_host, **options
      else
        # The method level `allow_other_host` doesn't apply in the fallback case, omit and let the `redirect_to` handling take over.
        redirect_to fallback_location, **options
      end
    end

    def _compute_redirect_to_location(request, options) # :nodoc:
      case options
      # The scheme name consist of a letter followed by any combination of
      # letters, digits, and the plus ("+"), period ("."), or hyphen ("-")
      # characters; and is terminated by a colon (":").
      # See https://tools.ietf.org/html/rfc3986#section-3.1
      # The protocol relative scheme starts with a double slash "//".
      when /\A([a-z][a-z\d\-+.]*:|\/\/).*/i
        options.to_str
      when String
        request.protocol + request.host_with_port + options
      when Proc
        _compute_redirect_to_location request, instance_eval(&options)
      else
        url_for(options)
      end.delete("\0\r\n")
    end
    module_function :_compute_redirect_to_location
    public :_compute_redirect_to_location

    # Verifies the passed +location+ is an internal URL that's safe to redirect to and returns it, or nil if not.
    # Useful to wrap a params provided redirect URL and fallback to an alternate URL to redirect to:
    #
    #   redirect_to url_from(params[:redirect_url]) || root_url
    #
    # The +location+ is considered internal, and safe, if it's on the same host as <tt>request.host</tt>:
    #
    #   # If request.host is example.com:
    #   url_from("https://example.com/profile") # => "https://example.com/profile"
    #   url_from("http://example.com/profile")  # => "http://example.com/profile"
    #   url_from("http://evil.com/profile")     # => nil
    #
    # Subdomains are considered part of the host:
    #
    #   # If request.host is on https://example.com or https://app.example.com, you'd get:
    #   url_from("https://dev.example.com/profile") # => nil
    #
    # NOTE: there's a similarity with {url_for}[rdoc-ref:ActionDispatch::Routing::UrlFor#url_for], which generates an internal URL from various options from within the app, e.g. <tt>url_for(@post)</tt>.
    # However, #url_from is meant to take an external parameter to verify as in <tt>url_from(params[:redirect_url])</tt>.
    def url_from(location)
      location = location.presence
      location if location && _url_host_allowed?(location)
    end

    private
      def _allow_other_host
        !raise_on_open_redirects
      end

      def _extract_redirect_to_status(options, response_options)
        if options.is_a?(Hash) && options.key?(:status)
          Rack::Utils.status_code(options.delete(:status))
        elsif response_options.key?(:status)
          Rack::Utils.status_code(response_options[:status])
        else
          302
        end
      end

      def _enforce_open_redirect_protection(location, allow_other_host:)
        if allow_other_host || _url_host_allowed?(location)
          location
        else
          raise UnsafeRedirectError, "Unsafe redirect to #{location.truncate(100).inspect}, pass allow_other_host: true to redirect anyway."
        end
      end

      def _url_host_allowed?(url)
        host = URI(url.to_s).host
        host == request.host || host.nil? && url.to_s.start_with?("/")
      rescue ArgumentError, URI::Error
        false
      end
  end
end