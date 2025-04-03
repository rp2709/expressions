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