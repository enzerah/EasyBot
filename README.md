# EasyBot

Bot core em C++ com suporte a scripts Python e comunicação via gRPC.

## 🏗️ Estrutura

- **EasyBot_DLL**: Core do bot (DLL x86) com sistema de hooks, eventos e mapeamento de jogo
- **EasyBot_Scripts**: Cliente Python para scripts customizados
- **Protobuf/gRPC**: Comunicação entre componentes

## 🚀 Build Automático (GitHub Actions)

[![Build EasyBot](https://github.com/wojtas99/EasyBot/actions/workflows/build.yml/badge.svg)](https://github.com/wojtas99/EasyBot/actions/workflows/build.yml)

O projeto compila automaticamente via GitHub Actions a cada push:

1. Vá em [Actions](../../actions/workflows/build.yml)
2. Selecione o último workflow executado
3. Baixe os artefatos compilados em `EasyBot-Release`

### ⏱️ Tempo de build:
- **Primeiro build**: ~45 minutos (instala todas as dependências)
- **Builds subsequentes**: ~10-15 minutos (usa cache do vcpkg)

## 🛠️ Build Local

### Pré-requisitos:
- Visual Studio 2022 com C++ (MSVC x86)
- CMake 3.16+
- Git (para submodules)

### Passos:

```powershell
# 1. Clone com submodules
git clone --recurse-submodules https://github.com/wojtas99/EasyBot.git
cd EasyBot

# 2. Configure vcpkg
cd third_party/vcpkg
.\bootstrap-vcpkg.bat
cd ../..

# 3. Configure e compile
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --parallel 4
```

### Saída:
- `Bot/EasyBot.dll` - DLL principal do bot
- `Bot/EasyBot_Scripts.exe` - Cliente de scripts

## 📦 Dependências

Instaladas automaticamente via vcpkg:
- **Protobuf** - Serialização de dados
- **gRPC** - Comunicação cliente/servidor

## 🔧 Desenvolvimento

### Estrutura de arquivos:

```
EasyBot/
├── src/
│   ├── EasyBot_DLL/         # Core do bot
│   │   └── BotCore/         # Classes principais
│   └── EasyBot_Scripts/     # Cliente Python
├── bot.proto                # Definições gRPC
└── third_party/vcpkg/       # Gerenciador de dependências
```

### Adicionar funcionalidade:

1. Edite `bot.proto` para adicionar novos serviços/mensagens
2. Implemente no servidor (`proto_functions_server.cpp`)
3. Use no cliente (`proto_functions_client.cpp` ou scripts Python)

## 📝 Licença

Ver arquivo [LICENSE](LICENSE)