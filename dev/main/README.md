#Interlecto WS Engine

This code should define the **Interlecto Web Service** engine and the
Interlecto Web Service application and extension library.

This should provide:
 * an **Interlecto WS** application library `ilecto_app.a` and
   respective C++ headers
 * an **Interlecto WS** extenssion library `ilecto_ext.a` and
   respective C++ headers
 * an **Interlecto WS** basic application `index.cgi` which is already
   capable of linking a config file, a database, and available
   extenssions; and dispatch content as HTML over HTTP.
 * an **Interlecto WS** basic API `api.cgi` which is already capable of
   linking a config file, a database, and available extenssions; and
   dispatch, load, and modify content through XML or JSON over HTTP.

Any new web application could use this `index.cgi`, or can develop its
own program from the `ilecto_app` library.

**Nota bene:** `ilecto_app` and `ilecto_ext` might be the same library
with the same headers, at least on early development.
