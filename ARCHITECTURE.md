# Arquitetura do EasyBot

## 📐 Visão Geral

O EasyBot é dividido em dois componentes principais que se comunicam via gRPC:

```
┌─────────────────────┐         gRPC         ┌──────────────────────┐
│   EasyBot_DLL       │ ◄─────────────────► │  EasyBot_Scripts     │
│   (Servidor)        │                      │  (Cliente)           │
│                     │                      │                      │
│ • Injeta no jogo    │                      │ • Scripts Python     │
│ • Hooks/Patches     │                      │ • Bot logic          │
│ • Lê memória        │                      │ • Automação          │
│ • Envia eventos     │                      │ • Interface CLI      │
└─────────────────────┘                      └──────────────────────┘
         ▲
         │
         ▼
    ┌─────────┐
    │  Jogo   │
    │ (32-bit)│
    └─────────┘
```

## 🏗️ Componentes

### 1. EasyBot_DLL

**Tipo**: Biblioteca compartilhada (DLL)  
**Arquitetura**: x86 (32-bit)  
**Linguagem**: C++17

#### Responsabilidades:
- Injeção no processo do jogo
- Hooking de funções do jogo (MinHook)
- Leitura/escrita de memória
- Pattern scanning
- Dispatcher de eventos
- Servidor gRPC

#### Principais Classes:

##### `Game`
Classe singleton que gerencia o estado do jogo:
- Referências para LocalPlayer, Map, Containers
- Ciclo de vida do jogo

##### `LocalPlayer`
Representa o jogador:
- HP, MP, posição, nível, skills
- Inventário
- Ações (andar, atacar, usar item)

##### `Map`
Gerencia o mapa do jogo:
- Tiles acessíveis
- Criaturas no mapa
- Pathfinding

##### `Container`
Gerencia inventário e containers:
- Slots de itens
- Operações (mover item, usar, etc)

##### `Creature`
Entidade de criatura/player:
- Nome, HP, posição, outfits
- Estados (em combate, seguindo, etc)

##### `EventDispatcher`
Sistema de eventos por tempo:
```cpp
EventDispatcher::addEvent(100ms, [](){
    // Código executado a cada 100ms
});
```

##### `hooks.cpp`
Interceptação de funções do jogo:
- Packets enviados/recebidos
- Renderização
- Entrada do usuário

#### Fluxo de Execução:

```
1. DLL injetada no processo
2. Inicializa MinHook
3. Escaneia patterns na memória
4. Instala hooks nas funções
5. Inicializa servidor gRPC
6. Aguarda chamadas RPC
```

### 2. EasyBot_Scripts

**Tipo**: Executável CLI  
**Linguagem**: Python 3.x + C++ wrapper

#### Responsabilidades:
- Cliente gRPC
- Scripts de automação em Python
- Interface de linha de comando
- Lógica de bot de alto nível

#### Arquivos principais:

##### `Bot_Functions.py`
Funções auxiliares Python:
```python
def walkTo(x, y, z):
    # Calcula path e anda
    
def attackCreature(name):
    # Busca e ataca criatura
```

##### `EasyBotPython_Scripts.py`
Scripts de bot principal:
```python
while True:
    # Loop principal do bot
    if hp_low():
        heal()
    if target_found():
        attack()
```

##### `bot_pb2.py` / `bot_pb2_grpc.py`
Stubs Python gerados do Protobuf

## 🔌 Comunicação gRPC

### Protocolo (bot.proto)

Define serviços e mensagens:

```protobuf
service BotService {
    rpc GetPlayerInfo(Empty) returns (PlayerInfo);
    rpc WalkToPosition(Position) returns (Result);
    rpc AttackCreature(CreatureName) returns (Result);
}

message PlayerInfo {
    string name = 1;
    int32 hp = 2;
    int32 maxHp = 3;
    Position position = 4;
}
```

### Implementação

**Servidor** (`proto_functions_server.cpp`):
```cpp
Status BotServiceImpl::GetPlayerInfo(...) {
    auto player = Game::getLocalPlayer();
    response->set_name(player->getName());
    response->set_hp(player->getHP());
    // ...
    return Status::OK;
}
```

**Cliente** (`proto_functions_client.cpp`):
```cpp
PlayerInfo getPlayerInfo() {
    Empty request;
    PlayerInfo response;
    stub_->GetPlayerInfo(&context, request, &response);
    return response;
}
```

**Python** (`Bot_Functions.py`):
```python
def get_player_info():
    return stub.GetPlayerInfo(Empty())
```

## 🛠️ Build System

### CMake Hierarquia

```
EasyBot/CMakeLists.txt
├── bot_proto (library)
├── src/EasyBot_DLL/CMakeLists.txt
│   └── EasyBotDLL (shared library)
└── src/EasyBot_Scripts/CMakeLists.txt
    └── EasyBotScripts (executable)
```

### vcpkg Integração

Dependências instaladas via vcpkg:
- **Protobuf**: Serialização
- **gRPC**: RPC framework

Triplet: `x86-windows-static` (linkagem estática)

## 🔐 Segurança e Anti-Cheat

### Considerações:

⚠️ **Disclaimer**: Este projeto é educacional. Uso em jogos online pode violar ToS.

### Técnicas de detecção:

1. **Detecção de DLL injetada**
   - Scanning de módulos carregados
   - Proteção: DLL manual mapping

2. **Detecção de hooks**
   - Verificação de integrity de funções
   - Proteção: Hooks via VEH

3. **Detecção de pattern scanning**
   - Monitoramento de VirtualQuery
   - Proteção: Scans pontuais, cache de results

4. **Detecção comportamental**
   - Movimentos muito precisos
   - Reações inumanas
   - Proteção: Randomização, delays

## 🧪 Testing

### Manual Testing:

1. Compile o projeto
2. Abra o jogo
3. Injete `EasyBot.dll` (via injector)
4. Execute `EasyBot_Scripts.exe`
5. Observe comportamento

### Debug:

- Use Visual Studio Debugger
- Attach ao processo do jogo
- Breakpoints em hooks

## 📊 Performance

### Métricas típicas:

- **Latência gRPC**: ~1-5ms (localhost)
- **CPU usage**: <5% (sem bot ativo)
- **Memória**: ~10-20MB (DLL)

### Otimizações:

- Events em vez de polling constante
- Cache de entidades do mapa
- Batch de operações gRPC

## 🔄 Ciclo de Vida

```
[Jogo iniciado]
     ↓
[Injetar DLL]
     ↓
[Patches aplicados]
     ↓
[gRPC server ativo]
     ↓
[Cliente conecta]
     ↓
[Script Python roda]
     ↓
[Chamadas RPC] ←→ [Ações no jogo]
     ↓
[Cliente desconecta]
     ↓
[Jogo fechado / DLL ejetada]
```

## 📚 Recursos Adicionais

- [gRPC Documentation](https://grpc.io/docs/)
- [MinHook Library](https://github.com/TsudaKageyu/minhook)
- [Protocol Buffers](https://developers.google.com/protocol-buffers)
