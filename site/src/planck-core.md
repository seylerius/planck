# planck.core

Core Planck functions for use in scripts.

[\*command-line-args\*](#command-line-args)<br/>
[\*err\*](#err)<br/>
[\*in\*](#in)<br/>
[\*planck-version\*](#planck-version)<br/>
[IBufferedReader](#IBufferedReader)<br/>
[IClosable](#IClosable)<br/>
[IInputStream](#IInputStream)<br/>
[IOutputStream](#IOutputStream)<br/>
[IReader](#IReader)<br/>
[eval](#eval)<br/>
[exit](#exit)<br/>
[file-seq](#file-seq)<br/>
[init-empty-state](#init-empty-state)<br/>
[intern](#intern)<br/>
[line-seq](#line-seq)<br/>
[ns-resolve](#ns-resolve)<br/>
[read-line](#read-line)<br/>
[read-password](#read-password)<br/>
[resolve](#resolve)<br/>
[slurp](#slurp)<br/>
[spit](#spit)<br/>
[with-open](#with-open)<br/>

## <a name="command-line-args"></a>\*command-line-args\*

A sequence of the supplied command line arguments, or `nil` if none were supplied

## <a name="err"></a>\*err\*

A `cljs.core/IWriter` representing standard error for print operations.

## <a name="in"></a>\*in\*
  A `planck.io/IReader` representing standard input for read operations.

## <a name="planck-version"></a>\*planck-version\*

A string containing the version of the Planck executable.

## <a name="IBufferedReader"></a>IBufferedReader
_Protocol_

Protocol for reading line-based content.

  `-read-line`<br/>
  `([this])`<br/>
  Reads the next line.


## <a name="IClosable"></a>IClosable
_Protocol_

  `-close`<br/>
  `([this])`

## <a name="IInputStream"></a>IInputStream
_Protocol_

  Protocol for reading binary data.

  `-read-bytes`<br/>
  `([this])`<br/>
  Returns available bytes as an array of unsigned numbers or `nil` if EOF.

## <a name="IOutputStream"></a>IOutputStream
_Protocol_

  Protocol for writing binary data.

  `-write-bytes`<br/>
  `([this byte-array])`<br/>
  Writes byte array.

  `-flush-bytes`<br/>
  `([this])`<br/>
  Flushes output.

## <a name="IReader"></a>IReader
_Protocol_

  Protocol for reading.

  `-read`<br/>
  `([this])`<br/>
  Returns available characters as a string or `nil` if EOF.

## <a name="eval"></a>eval
`([form])`

Evaluates the form data structure (not text!) and returns the result.

Spec<br/>
 _args_: `(cat :form any?)`<br/>
 _ret_: `any?`<br/>

## <a name="exit"></a>exit
`([exit-value])`

Causes Planck to terminate with the supplied `exit-value`.

Spec<br/>
 _args_: `(cat :exit-value integer?)`<br/>

## <a name="file-seq"></a>file-seq
`([dir])`

A tree seq on files

Spec<br/>
 _args_: `(cat :dir ::coercible-file?)`

## <a name="init-empty-state"></a>init-empty-state
`([state])`

An init function for use with `cljs.js/empty-state` which initializes
the empty state with `cljs.core` analysis metadata.

This is useful because Planck is built with `:dump-core` set to false.

Usage: `(cljs.js/empty-state init-empty-state)`

Spec<br/>
 _args_: `(cat :state map?)`<br/>
 _ret_: `map?`<br/>

## <a name=""></a>intern
`([ns name] [ns name val])`

Finds or creates a var named by the symbol `name` in the namespace
`ns` (which can be a symbol or a namespace), setting its root binding
to `val` if supplied. The namespace must exist. The var will adopt any
metadata from the `name` symbol.  Returns the var.

Spec<br/>
 _args_: `(cat :ns (or :sym symbol? :ns #(instance? Namespace %)) :name symbol? :val (? any?))`<br/>

## <a name="line-seq"></a>line-seq
`([rdr])`

Returns the lines of text from rdr as a lazy sequence of strings.
`rdr` must implement [`IBufferedReader`](#IBufferedReader).

Spec<br/>
 _args_: `(cat :rdr (instance? IBufferedReader %))`<br/>
 _ret_: `seq?`<br/>

## <a name="ns-resolve"></a>ns-resolve
`([ns sym])`

Returns the var to which a symbol will be resolved in the namespace,
else `nil`.

Spec<br/>
 _args_: `(cat :ns symbol? :sym symbol?)`<br/>
 _ret_: `(nilable var?)`<br/>

## <a name="read-line"></a>read-line
`([])`

  Reads the next line from the current value of `planck.io/*in*`

Spec<br/>
 _args_: `(cat )`<br/>
 _ret_: `string?`<br/>

## <a name="read-password"></a>read-password
`([] [prompt])`

  Reads the next line from console with echoing disabled.
  It will print out a prompt if supplied

Spec<br/>
 _args_: `(cat :prompt (? string?))`<br/>
 _ret_: `string?`<br/>

## <a name="resolve"></a>resolve
`([sym])`

  Returns the var to which a symbol will be resolved in the current
  namespace, else `nil`.

Spec<br/>
 _args_: `(cat :sym symbol?)`<br/>
 _ret_: `(nilable var?)`<br/>

## <a name="slurp"></a>slurp
`([f & opts])`

  Opens a reader on `f` and reads all its contents, returning a string.
  See `planck.io/reader` for a complete list of supported arguments.

Spec<br/>
 _args_: `(cat :f :planck.io/coercible-file? :opts (* any?))`<br/>
 ret: `string?`

## <a name="spit"></a>spit
`([f content & opts])`

  Opposite of `slurp`.  Opens `f` with `writer`, writes content, then
  closes `f`. Options passed to `planck.io/writer`.

Spec<br/>
 `args`: `(cat :f :planck.io/coercible-file? :content any? :opts (* any?))`

## <a name="with-open"></a>with-open
`([bindings & body])`

_Macro_

  `bindings` => `[name IClosable `...`]`

  Evaluates `body` in a `try` expression with names bound to the values
  of the inits, and a `finally` clause that calls `(-close name)` on each
  `name` in reverse order.
