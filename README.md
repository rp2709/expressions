# Expressions

Simple graphical calculator with a twist: it displays the binary tree used to evaluate the expressions

![illustration](./illustration.png)

It is only a small coding challenge and should only be viewed as such.


## Try it out
You will have to clone this repository and build from source.

```bash
git clone https://github.com/rp2709/expressions.git
```

In the newly created directory use the build and install script provided. As you should NEVER run a random script without first checking it, here it is in it's entierty:
```bash
echo "install gtkmm-4.0 using apt"
sudo apt install libgtkmm-4.0-dev

echo "install meson project"
meson builddir

echo "compile project"
ninja -Cbuilddir

echo "install for local user"
cp builddir/src/expressions ~/.local/bin/

echo "cleaning up"
rm -r builddir
```

As you can see, the executable is copied to your .local/bin directory, so you can use it as a command.

## Usage
Simply launch with 
```bash
expressions
```

You may want to see all the debug logs, then use
```bash
expressions --debug true
```
You can use these expressions to test the program:
- `1+(2+3)*4^2`
- `(((3.2 + (4.1 * (2.3 - 1.2))) / (6.5 - (2.2 ^ 3))) + 5.7)`
- `(((8.4 / (3.1 + (2.7 - 1.5))) ^ 2) - ((6.3 * (4.9 / 2.1)) + 3.6))`
