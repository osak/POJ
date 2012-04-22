#!/usr/bin/ruby

require 'nokogiri'
require 'open-uri'
require 'fileutils'

probno = ARGV[0].to_i

doc = Nokogiri::HTML(open("http://poj.org/problem?id=#{probno}"))
title = doc.css("div.ptt")[0].content

filename = sprintf("%04d.cc", probno)
if not FileTest.exist?(filename)
  File.open(filename, 'w') do |f|
    f.puts <<TEMPLATE
//Name: #{title}
//Level:
//Category:
//Note:

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}
TEMPLATE
  end
end

sinput = doc.css("pre.sio")[0].content.gsub(/\r\n/, "\n")
filename = sprintf("%04d.in", probno)
File.open(filename, 'w') do |f|
  f.puts(sinput)
end
