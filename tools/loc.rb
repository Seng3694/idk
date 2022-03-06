require 'optparse'

FileEntry = Struct.new(:name, :lines)

$commentInfo = {
  'c' => {:regular => '//', :multiStart => '/*', :multiEnd => '*/'},
  'h' => {:regular => '//', :multiStart => '/*', :multiEnd => '*/'},
  'cpp' => {:regular => '//', :multiStart => '/*', :multiEnd => '*/'},
  'hpp' => {:regular => '//', :multiStart => '/*', :multiEnd => '*/'},
  'inl' => {:regular => '//', :multiStart => '/*', :multiEnd => '*/'},
  'lua' => {:regular => '#', :multiStart => '--[===[', :multiEnd => '--]===]'},
  'rb' => {:regular => '#', :multiStart => '=begin', :multiEnd => '=end'},
  'py' => {:regular => '#', :multiStart => '"""', :multiEnd => '"""'},
  'cs' => {:regular => '//', :multiStart => '/*', :multiEnd => '*/'}
}

def count_lines_in_file(fileName, ignoreComments)
  fileExt = File.extname(fileName).strip.downcase[1..-1]
  cinfo = nil
  if ignoreComments and (not fileExt.nil?) and (not $commentInfo[fileExt].nil?)
    cinfo = $commentInfo[fileExt]
  end
  multiCommentBlock = false

  File.foreach(fileName).inject(0) do |count, line|
    line.strip!
    if not line.empty?
      if not cinfo.nil?
        if line.start_with?(cinfo[:multiStart])
          multiCommentBlock = true
          count
        elsif multiCommentBlock and line.start_with?(cinfo[:multiEnd])
          multiCommentBlock = false
          count
        elsif not multiCommentBlock and (not line.start_with?(cinfo[:regular]))
            count + 1
        else
          count
        end
      else
        count + 1
      end
    else
      count
    end
  end
end

options = {
  :filter => '',
  :exclude => '',
  :comments => false
}
OptionParser.new do |opt|
  opt.banner = 'Usage: loc.rb [options] root_directory'

  opt.on('-f', '--filter FILEFILTER', 'eg. "cpp hpp lua"') do |o| 
    options[:filter] = o 
  end
  opt.on('-e', '--exclude EXCLUDEDDIRS', 'eg. "ext .vs .git"') do |o| 
    options[:exclude] = o 
  end
  opt.on('-c', '--comments', TrueClass, 'ignores comments while counting lines.') do |o|
    options[:comments] = o.nil? ? true : o
  end
end.parse!

if ARGV.length == 1
  rootDirectory = ARGV[0]
else
  rootDirectory = Dir.pwd
end

Dir.chdir(rootDirectory)

if options[:filter].empty?
  fileFilter = '.*'
else
  fileFilter = '.{' << options[:filter].gsub(/[^0-9a-zA-Z ]/, '').split(' ').join(',') << '}'
end

excludedDirectories = options[:exclude].gsub('\\', '/').split(' ')

globFilter = '**/*' << fileFilter

fileNames = Dir.glob(globFilter)

fileEntries = []

for fileName in fileNames
  isValid = true
  for excludedDir in excludedDirectories
    if fileName.start_with?(excludedDir)
      isValid = false
      break
    end
  end

  if isValid
    fileEntries << FileEntry.new(fileName, count_lines_in_file(fileName, options[:comments]))
  end
end

if fileEntries.length == 0
  puts 'No files found'
  exit 0
end

fileEntries = fileEntries.sort_by(&:lines).reverse

maxFileNameLength = 0
maxLineCount = fileEntries[0].lines.to_s.length
totalLinesOfCode = 0

fileEntries.each do |entry|
  if entry.name.length > maxFileNameLength
    maxFileNameLength = entry.name.length
  end
  totalLinesOfCode += entry.lines
end

fileEntries.each do |entry|
  puts "#{entry.name.ljust(maxFileNameLength)} #{entry.lines.to_s.rjust(maxLineCount)}"
end

puts '_' * (maxFileNameLength + maxLineCount + 1)
puts "total #{totalLinesOfCode.to_s.rjust(maxLineCount + maxFileNameLength - 5)}"
