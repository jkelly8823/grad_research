      included do
        extend ActiveModel::Naming

        class_attribute :include_root_in_json, instance_writer: false
        self.include_root_in_json = false
      end

      # Returns a hash representing the model. Some configuration can be