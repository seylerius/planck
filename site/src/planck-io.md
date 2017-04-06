# planck.io

Planck I/O functionality.

Coercions
IOFactory
as-file
as-url
delete-file
directory?
file
file-attributes
input-stream
make-input-stream
make-output-stream
make-reader
make-writer
output-stream
reader
writer

## Coercions
_Protocol_

  Coerce between various 'resource-namish' things.

  `as-file`<br/>
  `([x])`<br/>
  Coerce argument to a `File`.

  `as-url`<br/>
  `([x])`<br/>
  Coerce argument to a `goog.Uri`.
  
## IOFactory
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
  
## as-file
([x])
  Coerce argument to a File.
  
## as-url
([x])
  Coerce argument to a goog.Uri.
  
## delete-file
([f])
  Delete file f.
Spec
 args: (cat :f ::coercible-file?)
 
## directory?
([dir])
  Checks if dir is a directory.
Spec
 args: (cat :dir ::coercible-file?)
 ret: boolean?
 
## file
([path] [parent & more])
  Returns a File for given path.  Multiple-arg
   versions treat the first argument as parent and subsequent args as
   children relative to the parent.
Spec
 args: (cat :path-or-parent string? :more (* string?))
 ret: (instance? File %)
 
## file-attributes
([path])
  Returns a map containing the attributes of the item at a given path.
Spec
 args: (cat :path ::coercible-file?)
 ret: map?
 
## input-stream
([x & opts])
  Attempts to coerce its argument into an open IInputStream.
  
## make-input-stream
([x opts])
  Creates an IInputStream. See also IOFactory docs.
  
## make-output-stream
([x opts])
  Creates an IOutputStream. See also IOFactory docs.
  
## make-reader
([x opts])
  Creates an IReader. See also IOFactory docs.
  
## make-writer
([x opts])
  Creates an IWriter. See also IOFactory docs.
  
## output-stream
([x & opts])
  Attempts to coerce its argument into an open IOutputStream.
  
## reader
([x & opts])
  Attempts to coerce its argument into an open IBufferedReader.
  
## writer
([x & opts])
  Attempts to coerce its argument into an open IWriter.
