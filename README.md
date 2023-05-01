This program uses [finwo/dep](https://github.com/finwo/dep) for managing
dependencies. Please visit that tool's repository for instructions on how to
install it.

---

### Installing dependencies

```sh
dep i
```

### Building

```sh
make
```

### Ze issue

**Expected behavior**:

The title of the window, as well as the string logged in the terminal, would
include the number generated on the javascript side.

**Actual behavior**:

The string printed by [main.c:33](src/main.c#L33) just prints "Reminder" instead
