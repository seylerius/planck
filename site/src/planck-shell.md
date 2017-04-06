# planck.shell

Planck Shell capability.

[\*sh-dir\*](#sh-dir)<br/>
[\*sh-env\*](#sh-env)<br/>
[sh](#sh)<br/>
[sh-async](#sh-async)<br/>
[with-sh-dir](#with-sh-dir)<br/>
[with-sh-env](#with-sh-env)<br/>

## <a name="sh-dir"></a>\*sh-dir\*

## <a name="sh-env"></a>\*sh-env\*

## <a name="sh"></a>sh
`([& args])`

Launches a sub-process with the supplied arguments.

Parameters: `cmd`, <`options`><br/>
  `cmd`      the command(s) (Strings) to execute. will be concatenated together.<br/>
  `options`  optional keyword arguments-- see below.<br/>

Options are:<br/>
  `:in`      may be given followed by a string of one of the following formats:<br/>
String conforming to URL Syntax: 'file:///tmp/test.txt'<br/>
String pointing at an *existing* 'file: '/tmp/test.txt'<br/>
String with string input: 'Printing input from stdin with funny chars like $@ &'
to be fed to the sub-process's stdin.<br/>
  `:in-enc`  option may be given followed by a String, used as a character
encoding name (for example "UTF-8" or "ISO-8859-1") to
convert the input string specified by the :in option to the
sub-process's stdin.  Defaults to UTF-8.<br/>
  `:out-enc` option may be given followed by a String. If a
String is given, it will be used as a character encoding
name (for example "UTF-8" or "ISO-8859-1") to convert
the sub-process's stdout to a String which is returned.<br/>
  `:env`    override the process env with a map of String: String.<br/>
  `:dir`     override the process dir with a String or planck.io/File.<br/>
  if the command can be launched, sh returns a map of<br/>
`:exit` => sub-process's exit code<br/>
`:out`  => sub-process's stdout (as String)<br/>
`:err`  => sub-process's stderr (String via platform default encoding),
  otherwise it throws an exception
  
Spec<br/>
 _args_: `(cat :cmd (+ string?) :opts (* ::sh-opt))`<br/>
 _ret_: `(keys :req-un [::exit ::out ::err])`
 
## <a name="sh-async"></a>sh-async
`([& args])`

Launches a sub-process with the supplied arguments.

Parameters: `cmd`, <`options`>, `cb`<br/>
  `cmd`      the command(s) (Strings) to execute. will be concatenated together.<br/>
  `options`  optional keyword arguments-- see below.<br/>
  `cb`       the callback to call upon completion

Options are:<br/>
  `:in`      may be given followed by a string of one of the following formats:<br/>
 String conforming to URL Syntax: 'file:///tmp/test.txt'<br/>
String pointing at an *existing* 'file: '/tmp/test.txt'<br/>
String with string input: 'Printing input from stdin with funny chars like $@ &'
to be fed to the sub-process's stdin.<br/>
  `:in-enc`  option may be given followed by a String, used as a character
encoding name (for example "UTF-8" or "ISO-8859-1") to
convert the input string specified by the :in option to the
sub-process's stdin.  Defaults to UTF-8.<br/>
  `:out-enc` option may be given followed by a String. If a
String is given, it will be used as a character encoding
name (for example "UTF-8" or "ISO-8859-1") to convert
the sub-process's stdout to a String which is returned.<br/>
  `:env`    override the process env with a map of String: String.<br/>
  `:dir`     override the process dir with a String or planck.io/File.<br/>
  if the command can be launched, sh returns a map of<br/>
`:exit` => sub-process's exit code<br/>
`:out`  => sub-process's stdout (as String)<br/>
`:err`  => sub-process's stderr (String via platform default encoding),
  otherwise it throws an exception

Spec<br/>
 _args_: `(cat :cmd (+ string?) :opts (* ::sh-opt) :cb fn?)`
 _ret_: `nil?`
   
## <a name="with-sh-dir"></a>with-sh-dir
`([dir & forms])`

_Macro_

Sets the directory for use with `sh`, see `sh` for details.
  
## <a name="with-sh-env"></a>with-sh-env
`([env & forms])`

_Macro_

Sets the environment for use with `sh`, see `sh` for details.