(ns planck.socket.alpha
  "Planck socket functionality."
  (:require
   [cljs.spec.alpha :as s]
   [planck.repl :as repl]))

(defrecord Socket [descriptor]
  Object
  (toString [this] (pr-str this)))

(defn ^boolean socket?
  "Returns true if x is a Socket."
  [x]
  (instance? Socket x))

(s/fdef socket?
  :args (s/cat :x any?)
  :ret boolean?)

(s/def ::host string?)
(s/def ::port integer?)
(s/def ::data string?)                                      ; Maybe also byte arrays in the future?
(s/def ::socket socket?)
(s/def ::data-handler (s/fspec :args (s/cat :socket ::socket :data (s/nilable ::data)) :ret nil?))
(s/def ::accept-handler (s/fspec :args (s/cat :socket ::socket) :ret ::data-handler))
(s/def ::opts (s/nilable map?))

(defn- wrap-data-handler
  "Wraps a data handler function to map between low-level descriptors and
  Socket instances."
  [data-handler]
  (fn [descriptor data]
    (data-handler (->Socket descriptor) data)))

(defn- wrap-accept-handler
  "Wraps an accept handler function to map between low-level descriptors and
  Socket instances."
  [accept-handler]
  (fn [descriptor]
    (wrap-data-handler (accept-handler (->Socket descriptor)))))

(defn connect
  "Connects a TCP socket to a remote host/port. The connected socket is
  returned. Data can be written to the socket using `write` and the socket can
  be closed using `close`.

  A data-handler argument must be supplied, which is a function that accepts a
  socket and a nillable data value. This data handler will be called when data
  arrives on the socket. When the socket is closed the data handler will be
  called with a nil data value."
  ([host port data-handler]
   (connect host port data-handler nil))
  ([host port data-handler opts]
   (->Socket (js/PLANCK_SOCKET_CONNECT host port (wrap-data-handler data-handler)))))

(s/fdef connect
  :args (s/cat :host ::host :port ::port :data-handler ::data-handler :opts (s/? ::opts))
  :ret ::socket)

(defn write
  "Writes data to a socket."
  ([socket data]
   (write socket data nil))
  ([socket data opts]
   (js/PLANCK_SOCKET_WRITE (.-descriptor socket) data)))

(s/fdef write
  :args (s/cat :socket ::socket :data ::data :opts (s/? ::opts)))

(defn close
  "Closes a socket."
  ([socket]
   (close socket nil))
  ([socket opts]
   (js/PLANCK_SOCKET_CLOSE (.-descriptor socket))))

(s/fdef close
  :args (s/cat :socket ::socket :opts (s/? ::opts))
  :ret nil?)

(defn listen
  "Opens a server socket, listening for inbound connections. The port to
  listen on must be specified, along with an accept-handler.

  The accept-handler should be a function that accepts a socket and returns a
  data handler.

  The data handler is a function that accepts a socket and a nillable data
  value. This data handler will be called when data arrives on the socket. When
  the socket is closed the data handler will be called with a nil data value.

  For example, an echo server could be written in this way:

    (listen 55555
      (fn [socket]
        (fn [socket data]
          (when data
            (write socket data)))))"
  ([port accept-handler]
   (listen port accept-handler nil))
  ([port accept-handler opts]
   (js/PLANCK_SOCKET_LISTEN port (wrap-accept-handler accept-handler))))

(s/fdef listen
  :args (s/cat :socket ::socket :accept-handler ::accept-handler :opts (s/? ::opts))
  :ret nil?)

(repl/register-speced-vars
  `connect
  `write
  `close
  `listen)
