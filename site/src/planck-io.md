# planck.io

Planck I/O functionality.

[Coercions](#Coercions)<br/>
[IOFactory](#IOFactory)<br/>
[as-file](#as-file)<br/>
[as-url](#as-url)<br/>
[delete-file](#delete-file)<br/>
[directory?](#directory?)<br/>
[file](#file)<br/>
[file-attributes](#file-attributes)<br/>
[input-stream](#input-stream)<br/>
[make-input-stream](#make-input-stream)<br/>
[make-output-stream](#make-output-stream)<br/>
[make-reader](#make-reader)<br/>
[make-writer](#make-writer)<br/>
[output-stream](#output-stream)<br/>
[reader](#reader)<br/>
[writer](#writer)<br/>

## <a name="Coercions"></a>Coercions
_Protocol_

  Coerce between various 'resource-namish' things.

  `as-file`<br/>
  `([x])`<br/>
  Coerce argument to a `File`.

  `as-url`<br/>
  `([x])`<br/>
  Coerce argument to a `goog.Uri`.
  
## <a name="IOFactory"></a>IOFactory
_Protocol_

  Factory functions that create ready-to-use versions of
  the various stream types, on top of anything that can
  be unequivocally converted to the requested kind of stream.

  Common options include

  `:append`   true to open stream in append mode<br/>
  `:encoding`  string name of encoding to use, e.g. "UTF-8".

  Callers should generally prefer the higher level API provided by
  `reader`, `writer`, `input-stream`, and `output-stream`.

  `make-reader`<br/>
  `([x opts])`<br/>
  Creates an `IReader`. See also `IOFactory` docs.

  `make-writer`<br/>
  `([x opts])`<br/>
  Creates an `IWriter`. See also `IOFactory` docs.

  `make-input-stream`<br/>
  `([x opts])`<br/>
  Creates an `IInputStream`. See also `IOFactory` docs.

  `make-output-stream`<br/>
  `([x opts])`<br/>
  Creates an `IOutputStream`. See also `IOFactory` docs.
  
## <a name="as-file"></a>as-file
`([x])`
 
Coerce argument to a `File`.
  
## <a name="as-url"></a>as-url
`([x])`

Coerce argument to a `goog.Uri`.
  
## <a name="delete-file"></a>delete-file
`([f])`
  
Delete file `f`.
Spec<br/>
 _args_: `(cat :f ::coercible-file?)`
 
## <a name=""></a>directory?
`([dir])`
  
Checks if `dir` is a directory.

Spec<br/>
 _args_: `(cat :dir ::coercible-file?)`<br/>
 _ret_: `boolean?`
 
## <a name="file"></a>file
`([path] [parent & more])`
  
Returns a `File` for given path.  Multiple-arg
versions treat the first argument as parent and subsequent args as
children relative to the parent.

Spec<br/>
 _args_: `(cat :path-or-parent string? :more (* string?))`<br/>
 _ret_: `(instance? File %)`
 
## <a name="file-attributes"></a>file-attributes
`([path])`
  
Returns a map containing the attributes of the item at a given `path`.

Spec
 _args_: `(cat :path ::coercible-file?)`<br/>
 _ret_: `map?`
 
## <a name="input-stream"></a>input-stream
`([x & opts])`

Attempts to coerce its argument into an open `IInputStream`.
  
## <a name="make-input-stream"></a>make-input-stream
`([x opts])`

Creates an `IInputStream`. See also `IOFactory` docs.
  
## <a name="make-output-stream"></a>make-output-stream
`([x opts])`
  
Creates an `IOutputStream`. See also `IOFactory` docs.
  
## <a name="make-reader"></a>make-reader
`([x opts])`

Creates an `IReader`. See also `IOFactory` docs.
  
## <a name="make-writer"></a>make-writer
`([x opts])`

Creates an `IWriter`. See also `IOFactory` docs.
  
## <a name="output-stream"></a>output-stream
`([x & opts])`

Attempts to coerce its argument into an open `IOutputStream`.
  
## <a name="reader"></a>reader
`([x & opts])`

Attempts to coerce its argument into an open `IBufferedReader`.
  
## <a name="writer"></a>writer
`([x & opts])`

Attempts to coerce its argument into an open `IWriter`.
