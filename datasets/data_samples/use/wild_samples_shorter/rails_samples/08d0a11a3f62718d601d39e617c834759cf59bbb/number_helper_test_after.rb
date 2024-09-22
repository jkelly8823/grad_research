    assert_equal "555-1234", number_to_phone(5551234)
    assert_equal "(800) 555-1212 x 123", number_to_phone(8005551212, area_code: true, extension: 123)
    assert_equal "+18005551212", number_to_phone(8005551212, country_code: 1, delimiter: "")
    assert_equal "+&lt;script&gt;&lt;/script&gt;8005551212", number_to_phone(8005551212, country_code: "<script></script>", delimiter: "")
    assert_equal "8005551212 x &lt;script&gt;&lt;/script&gt;", number_to_phone(8005551212, extension: "<script></script>", delimiter: "")
  end

  def test_number_to_currency
    assert_equal nil, number_to_currency(nil)
    assert_equal "$1,234,567,892", number_to_currency(1234567891.50, precision: 0)
    assert_equal "1,234,567,890.50 - K&#269;", number_to_currency("-1234567890.50", unit: raw("K&#269;"), format: "%n %u", negative_format: "%n - %u")
    assert_equal "&amp;pound;1,234,567,890.50", number_to_currency("1234567890.50", unit: "&pound;")
    assert_equal "&lt;b&gt;1,234,567,890.50&lt;/b&gt; $", number_to_currency("1234567890.50", format: "<b>%n</b> %u")
    assert_equal "&lt;b&gt;1,234,567,890.50&lt;/b&gt; $", number_to_currency("-1234567890.50", negative_format: "<b>%n</b> %u")
    assert_equal "&lt;b&gt;1,234,567,890.50&lt;/b&gt; $", number_to_currency("-1234567890.50", 'negative_format' => "<b>%n</b> %u")
  end

  def test_number_to_percentage
    assert_equal nil, number_to_percentage(nil)
    assert_equal "100.000%", number_to_percentage(100)
    assert_equal "100.000 %", number_to_percentage(100, format: '%n %')
    assert_equal "&lt;b&gt;100.000&lt;/b&gt; %", number_to_percentage(100, format: '<b>%n</b> %')
    assert_equal "<b>100.000</b> %", number_to_percentage(100, format: raw('<b>%n</b> %'))
    assert_equal "100%", number_to_percentage(100, precision: 0)
    assert_equal "123.4%", number_to_percentage(123.400, precision: 3, strip_insignificant_zeros: true)
    assert_equal "1.000,000%", number_to_percentage(1000, delimiter: ".", separator: ",")
  end
    assert_equal "489.0 Thousand", number_to_human(489000, precision: 4, strip_insignificant_zeros: false)
  end

  def test_number_to_human_escape_units
    volume = { unit: "<b>ml</b>", thousand: "<b>lt</b>", million: "<b>m3</b>", trillion: "<b>km3</b>", quadrillion: "<b>Pl</b>" }
    assert_equal '123 &lt;b&gt;lt&lt;/b&gt;', number_to_human(123456, :units => volume)
    assert_equal '12 &lt;b&gt;ml&lt;/b&gt;', number_to_human(12, :units => volume)
    assert_equal '1.23 &lt;b&gt;m3&lt;/b&gt;', number_to_human(1234567, :units => volume)
    assert_equal '1.23 &lt;b&gt;km3&lt;/b&gt;', number_to_human(1_234_567_000_000, :units => volume)
    assert_equal '1.23 &lt;b&gt;Pl&lt;/b&gt;', number_to_human(1_234_567_000_000_000, :units => volume)

    #Including fractionals
    distance = { mili: "<b>mm</b>", centi: "<b>cm</b>", deci: "<b>dm</b>", unit: "<b>m</b>",
                 ten: "<b>dam</b>", hundred: "<b>hm</b>", thousand: "<b>km</b>",
                 micro: "<b>um</b>", nano: "<b>nm</b>", pico: "<b>pm</b>", femto: "<b>fm</b>"}
    assert_equal '1.23 &lt;b&gt;mm&lt;/b&gt;', number_to_human(0.00123, :units => distance)
    assert_equal '1.23 &lt;b&gt;cm&lt;/b&gt;', number_to_human(0.0123, :units => distance)
    assert_equal '1.23 &lt;b&gt;dm&lt;/b&gt;', number_to_human(0.123, :units => distance)
    assert_equal '1.23 &lt;b&gt;m&lt;/b&gt;', number_to_human(1.23, :units => distance)
    assert_equal '1.23 &lt;b&gt;dam&lt;/b&gt;', number_to_human(12.3, :units => distance)
    assert_equal '1.23 &lt;b&gt;hm&lt;/b&gt;', number_to_human(123, :units => distance)
    assert_equal '1.23 &lt;b&gt;km&lt;/b&gt;', number_to_human(1230, :units => distance)
    assert_equal '1.23 &lt;b&gt;um&lt;/b&gt;', number_to_human(0.00000123, :units => distance)
    assert_equal '1.23 &lt;b&gt;nm&lt;/b&gt;', number_to_human(0.00000000123, :units => distance)
    assert_equal '1.23 &lt;b&gt;pm&lt;/b&gt;', number_to_human(0.00000000000123, :units => distance)
    assert_equal '1.23 &lt;b&gt;fm&lt;/b&gt;', number_to_human(0.00000000000000123, :units => distance)
  end

  def test_number_helpers_escape_delimiter_and_separator
    assert_equal "111&lt;script&gt;&lt;/script&gt;111&lt;script&gt;&lt;/script&gt;1111", number_to_phone(1111111111, delimiter: "<script></script>")

    assert_equal "$1&lt;script&gt;&lt;/script&gt;01", number_to_currency(1.01, separator: "<script></script>")
    assert_equal "100&lt;script&gt;&lt;/script&gt;000 Quadrillion", number_to_human(10**20, delimiter: "<script></script>")
  end

  def test_number_to_human_with_custom_translation_scope
    I18n.backend.store_translations 'ts',
      :custom_units_for_number_to_human => {:mili => "mm", :centi => "cm", :deci => "dm", :unit => "m", :ten => "dam", :hundred => "hm", :thousand => "km"}
    assert_equal "1.01 cm", number_to_human(0.0101, :locale => 'ts', :units => :custom_units_for_number_to_human)
  end

  def test_number_helpers_outputs_are_html_safe
    assert number_to_human(1).html_safe?
    assert !number_to_human("<script></script>").html_safe?
    assert number_to_human("asdf".html_safe).html_safe?