    # would set the session cookie to expire automatically 14 days after creation.
    # Other useful options include <tt>:key</tt>, <tt>:secure</tt> and
    # <tt>:httponly</tt>.
    class CookieStore < AbstractStore
      def initialize(app, options = {})
        super(app, options.merge!(cookie_only: true))
      end

      def delete_session(req, session_id, options)
        new_sid = generate_sid unless options[:drop]
        # Reset hash and Assign the new session id
        req.set_header("action_dispatch.request.unsigned_session_cookie", new_sid ? { "session_id" => new_sid } : {})
        new_sid
      end

      def load_session(req)
        stale_session_check! do
          data = unpacked_cookie_data(req)
          data = persistent_session_id!(data)
          [data["session_id"], data]
        end
      end

      private
        def extract_session_id(req)
          stale_session_check! do
            unpacked_cookie_data(req)["session_id"]
          end
        end

        def unpacked_cookie_data(req)

        def persistent_session_id!(data, sid = nil)
          data ||= {}
          data["session_id"] ||= sid || generate_sid
          data
        end

        def write_session(req, sid, session_data, options)
          session_data["session_id"] = sid
          session_data
        end

        def set_cookie(request, session_id, cookie)
          cookie_jar(request)[@key] = cookie