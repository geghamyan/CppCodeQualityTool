pushd ..
if [ ! -d vcpkg ]; then
    git clone https://github.com/microsoft/vcpkg.git 
fi

if [ ! -f ./vcpkg/vcpkg.exe ]; then
    cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics
fi
popd

if [ ! -f vcpkg.json ]; then
    vcpkg new --application
fi
vcpkg add port fmt
