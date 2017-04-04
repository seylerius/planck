# planck.core

## \*command-line-args\*

A sequence of the supplied command line arguments, or `nil` if none were supplied

## \*err\*

A `cljs.core/IWriter` representing standard error for print operations.

planck.core/*in*
  A planck.io/IReader representing standard input for read operations.

## \*planck-version\*

## IBufferedReader
Protocol
  Protocol for reading line-based content.

  -read-line
  ([this])
  Reads the next line.


## IClosable
Protocol

  -close
  ([this])

## planck.core/IInputStream
Protocol
  Protocol for reading binary data.

  -read-bytes
  ([this])
  Returns available bytes as an array of unsigned numbers or nil if EOF.

## planck.core/IOutputStream
Protocol
  Protocol for writing binary data.

  -write-bytes
  ([this byte-array])
  Writes byte array.

  -flush-bytes
  ([this])
  Flushes output.

# planck.core/IReader
Protocol
  Protocol for reading.

  -read
  ([this])
  Returns available characters as a string or nil if EOF.

# `eval`
`([form])`

Evaluates the form data structure (not text!) and returns the result.

Spec<br/>
 args: `(cat :form any?)`<br/>
 ret: `any?`<br/>

# `exit`
`([exit-value])`

Causes Planck to terminate with the supplied `exit-value`.

Spec<br/>
 args: `(cat :exit-value integer?)`<br/>

# `file-seq`
`([dir])`

A tree seq on files

Spec
 args: `(cat :dir ::coercible-file?)`

# `init-empty-state`
`([state])`

An init function for use with cljs.js/empty-state which initializes
the empty state with cljs.core analysis metadata.

This is useful because Planck is built with :dump-core set to false.

Usage: `(cljs.js/empty-state init-empty-state)`

Spec
 args: `(cat :state map?)`<br/>
 ret: `map?`<br/>

# intern
`([ns name] [ns name val])`

Finds or creates a var named by the symbol name in the namespace
ns (which can be a symbol or a namespace), setting its root binding
to val if supplied. The namespace must exist. The var will adopt any
metadata from the name symbol.  Returns the var.

Spec
 args: `(cat :ns (or :sym symbol? :ns #(instance? Namespace %)) :name symbol? :val (? any?))`<br/>

# line-seq
`([rdr])`

Returns the lines of text from rdr as a lazy sequence of strings.
rdr must implement IBufferedReader.

Spec
 args: `(cat :rdr (instance? IBufferedReader %))`<br/>
 ret: `seq?`<br/>

# `ns-resolve`
`([ns sym])`

Returns the var to which a symbol will be resolved in the namespace,
else nil.

Spec

 args: `(cat :ns symbol? :sym symbol?)`<br/>
 ret: `(nilable var?)`<br/>

# `read-line`
`([])`

  Reads the next line from the current value of planck.io/*in*

Spec
 args: `(cat )`<br/>
 ret: `string?`<br/>

# `read-password`
`([] [prompt])`

  Reads the next line from console with echoing disabled.
  It will print out a prompt if supplied

Spec
 args: `(cat :prompt (? string?))`<br/>
 ret: `string?`<br/>

# resolve
`([sym])`

  Returns the var to which a symbol will be resolved in the current
  namespace, else nil.

Spec
 args: `(cat :sym symbol?)`<br/>
 ret: `(nilable var?)`<br/>

# slurp
`([f & opts])`

  Opens a reader on f and reads all its contents, returning a string.
  See planck.io/reader for a complete list of supported arguments.

Spec
 args: `(cat :f :planck.io/coercible-file? :opts (* any?))`
 ret: `string?

# spit
`([f content & opts])`

  Opposite of slurp.  Opens f with writer, writes content, then
  closes f. Options passed to planck.io/writer.

Spec
 args: `(cat :f :planck.io/coercible-file? :content any? :opts (* any?))`

# with-open
`([bindings & body])`

Macro
  bindings => [name IClosable ...]

  Evaluates body in a try expression with names bound to the values
  of the inits, and a finally clause that calls (-close name) on each
  name in reverse order.
