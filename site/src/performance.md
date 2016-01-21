## Performance

<img width="85" align="right" style="margin: 0ex 1em" src="img/performance.jpg">
Planck can be very fast, especially since it depends on JavaScriptCore, which is great for minimizing startup latency. This makes it very useable for quickly starting up a REPL or running simple scripts.

### Caching

Planck executes scripts by compiling the ClojureScript to JavaScript for execution in JavaScriptCore. This is done dynamically and is usually very fast.

But, if you have scripts that don't change frequently, or are making use of large libraries, and the ClojureScript is expensive to compile, it may make sense to save the resulting JavaScript so that subsequent script execution can bypass compilation.

This means that if you re-run Planck and use namespaces that have been cached, the JavaScript representing those namespaces is simply loaded into JavaScriptCore. 

To enable compilation caching in Planck, you simply need to pass the `-k` or `--cache` option, specifying a directory into which Planck can write cache files. Here's an example: Let's say you have a foo.cljs script file that you run via

```sh
planck foo.cljs
```

First make an empty cache directory.

```
mkdir cache
```

Now you can tell Planck to use this directory for caching:

```
planck -k cache foo.cljs
```

The first time you run Planck this way, it will save the results of compilation into your cache directory. Then subsequent executions will use the cached results instead.

In addition to caching compiled JavaScript, the associated analysis metadata is cached. This makes it possible for Planck to know the symbols in a namespace, their docstrings, etc., without having to consult the original source. For additional speed, this analysis metadata is written using Transit instead of, say, edn as is currently done today by the ClojureScript compiler.

This caching works for

* top-level files like the example above (in which case it is assumed that the forms are in the `cljs.user` namespace, for caching purposes)
* ClojureScript files in a source directory
* code obtained from JARs

The caching mechanism works whether your are running planck to execute a script, or if you are invoking require in an interactive REPL session.

Planck uses a (naïve) file timestamp mechanism to know if cache files are stale, and it additionally looks at comments like the following

```
// Compiled by ClojureScript 1.7.170 {:static-fns-true}
```

in the compiled JavaScript to see if the files are applicable. If a file can’t be used, it is replaced with an updated copy.

Planck's cache invalidation strategy is _naïve_ because it doesn’t attempt to do sophisticated dependency graph analysis. So, there may be corner cases where you have to manually delete the contents of your cache directory, especially if the cached code involved macroexpansion and macro definitions have changed, for example.

### Static Dispatch

Also works around bad bug
