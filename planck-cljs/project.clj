(defproject planck "0.1.0"
  :profiles {:dev
             {:dependencies [[org.clojure/clojurescript "1.9.562"]
                             [org.clojure/test.check "0.10.0-alpha1"]
                             [tubular "1.0.0"]]
              :source-paths ["dev"]}
             :build-release 
             {}
             :build-commit
             {}}
  :dependencies [[org.clojure/clojure "1.8.0"]
                 [org.clojure/clojurescript "1.9.562"]
                 [org.clojure/test.check "0.10.0-alpha1"]
                 [org.clojure/tools.reader "1.0.0-RC1"]
                 [com.cognitect/transit-clj "0.8.300"]
                 [com.cognitect/transit-cljs "0.8.239"]
                 [fipp "0.6.8"]
                 [malabarba/lazy-map "1.3"]
                 [cljsjs/parinfer "1.8.1-0"]]
  :clean-targets ["out" "target"])
