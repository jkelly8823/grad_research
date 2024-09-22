
  private

    def query(path, exts, formats)
      query = ""
      EXTENSIONS.each_key do |ext|
        query << '(' << exts[ext].map {|e| e && Regexp.escape(".#{e}") }.join('|') << '|)'
      end
  end

  class NullResolver < PathResolver
    def query(path, exts, formats)
      handler, format, variant = extract_handler_and_format_and_variant(path, formats)
      [ActionView::Template.new("Template generated by Null Resolver", path.virtual, handler, :virtual_path => path.virtual, :format => format, :variant => variant)]
    end
  end