  #     XML_TYPE_NAMES = {
  #       "Symbol"     => "symbol",
  #       "Fixnum"     => "integer",
  #       "Bignum"     => "integer",
  #       "BigDecimal" => "decimal",
  #       "Float"      => "float",
  #       "TrueClass"  => "boolean",
  #       "FalseClass" => "boolean",
  #       "Date"       => "date",
  #       "DateTime"   => "dateTime",
  #       "Time"       => "dateTime"
  #     }
  #
  # By default the root node is "hash", but that's configurable via the <tt>:root</tt> option.
  #
  # The default XML builder is a fresh instance of <tt>Builder::XmlMarkup</tt>. You can
  # configure your own builder with the <tt>:builder</tt> option. The method also accepts
  # options like <tt>:dasherize</tt> and friends, they are forwarded to the builder.
  def to_xml(options = {})
    require 'active_support/builder' unless defined?(Builder)

    options = options.dup
    options[:indent]  ||= 2
    options[:root]    ||= 'hash'
    options[:builder] ||= Builder::XmlMarkup.new(indent: options[:indent])

    builder = options[:builder]
    builder.instruct! unless options.delete(:skip_instruct)

    root = ActiveSupport::XmlMini.rename_key(options[:root].to_s, options)

    builder.tag!(root) do
      each { |key, value| ActiveSupport::XmlMini.to_tag(key, value, options) }
      yield builder if block_given?
    end
  end

  class << self
    # Returns a Hash containing a collection of pairs when the key is the node name and the value is
    # its content
    #
    #   xml = <<-XML
    #     <?xml version="1.0" encoding="UTF-8"?>
    #       <hash>
    #         <foo type="integer">1</foo>
    #         <bar type="integer">2</bar>
    #       </hash>
    #   XML
    #
    #   hash = Hash.from_xml(xml)
    #   # => {"hash"=>{"foo"=>1, "bar"=>2}}
    def from_xml(xml)
      ActiveSupport::XMLConverter.new(xml).to_h
    end

  end
end

module ActiveSupport
  class XMLConverter # :nodoc:
    def initialize(xml)
      @xml = normalize_keys(XmlMini.parse(xml))
    end

    def to_h
      deep_to_h(@xml)
    end

    private

      def normalize_keys(params)
        case params
          when Hash
            Hash[params.map { |k,v| [k.to_s.tr('-', '_'), normalize_keys(v)] } ]
          when Array
            params.map { |v| normalize_keys(v) }
          else
            params
        end
      end

      def deep_to_h(value)
        case value
          when Hash
            process_hash(value)
          when Array
            process_array(value)
          when String
            value
          else
            raise "can't typecast #{value.class.name} - #{value.inspect}"
        end
      end

      def process_hash(value)
        if become_array?(value)
          _, entries = Array.wrap(value.detect { |k,v| not v.is_a?(String) })
          if entries.nil? || value['__content__'].try(:empty?)
            []
          else
            case entries
            when Array
              entries.collect { |v| deep_to_h(v) }
            when Hash
              [deep_to_h(entries)]
            else
              raise "can't typecast #{entries.inspect}"
            end
          end
        elsif become_content?(value)
          process_content(value)

        elsif become_empty_string?(value)
          ''
        elsif become_hash?(value)
          xml_value = Hash[value.map { |k,v| [k, deep_to_h(v)] }]

          # Turn { files: { file: #<StringIO> } } into { files: #<StringIO> } so it is compatible with
          # how multipart uploaded files from HTML appear
          xml_value['file'].is_a?(StringIO) ? xml_value['file'] : xml_value
        end
      end

      def become_content?(value)
        value['type'] == 'file' || (value['__content__'] && (value.keys.size == 1 || value['__content__'].present?))
      end

      def become_array?(value)
        value['type'] == 'array'
      end

      def become_empty_string?(value)
        # {"string" => true}
        # No tests fail when the second term is removed.
        value['type'] == 'string' && value['nil'] != 'true'
      end

      def become_hash?(value)
        !nothing?(value) && !garbage?(value)
      end

      def nothing?(value)
        # blank or nil parsed values are represented by nil
        value.blank? || value['nil'] == 'true'
      end

      def garbage?(value)
        # If the type is the only element which makes it then
        # this still makes the value nil, except if type is
        # a XML node(where type['value'] is a Hash)
        value['type'] && !value['type'].is_a?(::Hash) && value.size == 1
      end

      def process_content(value)
        content = value['__content__']
        if parser = ActiveSupport::XmlMini::PARSING[value['type']]
          parser.arity == 1 ? parser.call(content) : parser.call(content, value)
        else
          content
        end
      end

      def process_array(value)
        value.map! { |i| deep_to_h(i) }
        value.length > 1 ? value : value.first
      end

  end
end

  #     XML_TYPE_NAMES = {
  #       "Symbol"     => "symbol",
  #       "Fixnum"     => "integer",
  #       "Bignum"     => "integer",
  #       "BigDecimal" => "decimal",
  #       "Float"      => "float",
  #       "TrueClass"  => "boolean",
  #       "FalseClass" => "boolean",
  #       "Date"       => "date",
  #       "DateTime"   => "dateTime",
  #       "Time"       => "dateTime"
  #     }
  #
  # By default the root node is "hash", but that's configurable via the <tt>:root</tt> option.
  #
  # The default XML builder is a fresh instance of <tt>Builder::XmlMarkup</tt>. You can
  # configure your own builder with the <tt>:builder</tt> option. The method also accepts
  # options like <tt>:dasherize</tt> and friends, they are forwarded to the builder.
  def to_xml(options = {})
    require 'active_support/builder' unless defined?(Builder)

    options = options.dup
    options[:indent]  ||= 2
    options[:root]    ||= 'hash'
    options[:builder] ||= Builder::XmlMarkup.new(indent: options[:indent])

    builder = options[:builder]
    builder.instruct! unless options.delete(:skip_instruct)

    root = ActiveSupport::XmlMini.rename_key(options[:root].to_s, options)

    builder.tag!(root) do
      each { |key, value| ActiveSupport::XmlMini.to_tag(key, value, options) }
      yield builder if block_given?
    end
  end

  class << self
    # Returns a Hash containing a collection of pairs when the key is the node name and the value is
    # its content
    #
    #   xml = <<-XML
    #     <?xml version="1.0" encoding="UTF-8"?>
    #       <hash>
    #         <foo type="integer">1</foo>
    #         <bar type="integer">2</bar>
    #       </hash>
    #   XML
    #
    #   hash = Hash.from_xml(xml)
    #   # => {"hash"=>{"foo"=>1, "bar"=>2}}
    def from_xml(xml)
      ActiveSupport::XMLConverter.new(xml).to_h
    end

  end
end

module ActiveSupport
  class XMLConverter # :nodoc:
    def initialize(xml)
      @xml = normalize_keys(XmlMini.parse(xml))
    end

    def to_h
      deep_to_h(@xml)
    end

    private

      def normalize_keys(params)
        case params
          when Hash
            Hash[params.map { |k,v| [k.to_s.tr('-', '_'), normalize_keys(v)] } ]
          when Array
            params.map { |v| normalize_keys(v) }
          else
            params
        end
      end

      def deep_to_h(value)
        case value
          when Hash
            process_hash(value)
          when Array
            process_array(value)
          when String
            value
          else
            raise "can't typecast #{value.class.name} - #{value.inspect}"
        end
      end

      def process_hash(value)
        if become_array?(value)
          _, entries = Array.wrap(value.detect { |k,v| not v.is_a?(String) })
          if entries.nil? || value['__content__'].try(:empty?)
            []
          else
            case entries
            when Array
              entries.collect { |v| deep_to_h(v) }
            when Hash
              [deep_to_h(entries)]
            else
              raise "can't typecast #{entries.inspect}"
            end
          end
        elsif become_content?(value)
          process_content(value)

        elsif become_empty_string?(value)
          ''
        elsif become_hash?(value)
          xml_value = Hash[value.map { |k,v| [k, deep_to_h(v)] }]

          # Turn { files: { file: #<StringIO> } } into { files: #<StringIO> } so it is compatible with
          # how multipart uploaded files from HTML appear
          xml_value['file'].is_a?(StringIO) ? xml_value['file'] : xml_value
        end
      end

      def become_content?(value)
        value['type'] == 'file' || (value['__content__'] && (value.keys.size == 1 || value['__content__'].present?))
      end

      def become_array?(value)
        value['type'] == 'array'
      end

      def become_empty_string?(value)
        # {"string" => true}
        # No tests fail when the second term is removed.
        value['type'] == 'string' && value['nil'] != 'true'
      end

      def become_hash?(value)
        !nothing?(value) && !garbage?(value)
      end

      def nothing?(value)
        # blank or nil parsed values are represented by nil
        value.blank? || value['nil'] == 'true'
      end

      def garbage?(value)
        # If the type is the only element which makes it then
        # this still makes the value nil, except if type is
        # a XML node(where type['value'] is a Hash)
        value['type'] && !value['type'].is_a?(::Hash) && value.size == 1
      end

      def process_content(value)
        content = value['__content__']
        if parser = ActiveSupport::XmlMini::PARSING[value['type']]
          parser.arity == 1 ? parser.call(content) : parser.call(content, value)
        else
          content
        end
      end

      def process_array(value)
        value.map! { |i| deep_to_h(i) }
        value.length > 1 ? value : value.first
      end

  end
end
