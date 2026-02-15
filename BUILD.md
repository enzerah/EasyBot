# Configuração de Build do EasyBot

Este documento detalha as configurações de build do projeto.

## CMake

### Configurações principais:

```cmake
CMAKE_CXX_STANDARD = 17
CMAKE_MSVC_RUNTIME_LIBRARY = "MultiThreaded"
VCPKG_TARGET_TRIPLET = x86-windows-static
```

### Build Types:

- **Release**: Otimizado para performance (padrão)
- **Debug**: Com símbolos de debug

## vcpkg

### Triplets usados:

- **x86-windows-static**: Linkagem estática, arquitetura 32-bit
  - Usado para compatibilidade com jogos 32-bit
  - Gera binários standalone (sem DLLs externas)

### Dependências gerenciadas:

```json
{
  "dependencies": ["protobuf", "grpc"]
}
```

## GitHub Actions

### Cache otimizado:

O workflow usa cache em múltiplas camadas:

1. **vcpkg/packages**: Pacotes compilados (~2 GB)
2. **vcpkg/installed**: Headers e libs instaladas
3. **vcpkg/buildtrees**: Árvores de build intermediárias

### Matriz de build:

Atualmente compilamos apenas:
- **Release/x86-windows-static**

Para adicionar mais configurações, edite `.github/workflows/build.yml`:

```yaml
strategy:
  matrix:
    build-type: [Release, Debug]
    arch: [x86, x64]
```

## Compilação Manual Avançada

### Forçar rebuild do vcpkg:

```powershell
cd third_party/vcpkg
.\vcpkg.exe remove --recurse protobuf grpc
.\vcpkg.exe install protobuf:x86-windows-static grpc:x86-windows-static
```

### Build com Ninja (mais rápido):

```powershell
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
```

### Build verbose:

```powershell
cmake --build . --config Release --verbose
```

## Troubleshooting

### Erro: "grpc_cpp_plugin not found"

O CMakeLists.txt agora busca automaticamente em múltiplos paths:
1. `third_party/vcpkg/packages/grpc_*/tools/grpc/`
2. `third_party/vcpkg/installed/*/tools/grpc/`
3. PATH do sistema

### Cache corrompido do vcpkg:

```powershell
rm -r -fo third_party/vcpkg/packages
rm -r -fo third_party/vcpkg/buildtrees
```

### Build limpo:

```powershell
rm -r -fo build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```
