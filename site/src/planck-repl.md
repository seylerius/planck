# planck.repl

## \*pprint-results\*

`*pprint-results*` controls whether Planck REPL results are
pretty printed. If it is bound to logical false, results
are printed in a plain fashion. Otherwise, results are
pretty printed.
  
## apropos
`([str-or-pattern])`

_Macro_

Given a regular expression or stringable thing, return a seq of all
public definitions in all currently-loaded namespaces that match the
`str-or-pattern`.

## dir
`([nsname])`

_Macro_

Prints a sorted directory of public vars in a namespace

## doc
`([sym])`

_Macro_

Prints documentation for a var or special form given its name
  
## find-doc
`([re-string-or-pattern])`

_Macro_

Prints documentation for any var whose documentation or name
contains a match for `re-string-or-pattern`
  
## pst
`([] [e])`

_Macro_

Prints a stack trace of the exception.

If none supplied, uses the root cause of the most recent repl exception (`*e`)
  
## source
`([sym])`

_Macro_

Prints the source code for the given symbol, if it can find it.
This requires that the symbol resolve to a Var defined in a
namespace for which the source is available.

Example: `(source filter)`
  