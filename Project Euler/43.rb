puts [2, 3, 5, 7, 11, 13, 17].reduce([*100...1000]) { |obj, p| obj.product([*0..9]).map { |x, y| x * 10 + y }.select { |x| x % 1000 % p == 0 && x.to_s.chars.uniq.length == x.to_s.length } }.reduce(:+)