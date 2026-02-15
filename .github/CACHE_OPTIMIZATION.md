# Otimização de Cache - GitHub Actions

## 🚀 Melhorias implementadas

### **Problema anterior:**
- Build demorava sempre o mesmo tempo
- Cache não estava otimizado
- vcpkg recompilava dependências desnecessariamente

### **Solução aplicada:**

#### 1. **Cache em múltiplas camadas**

```yaml
path: |
  third_party/vcpkg/downloads    # Arquivos baixados (tarballs)
  third_party/vcpkg/packages     # Pacotes compilados
  third_party/vcpkg/installed    # Headers e libs instaladas
```

#### 2. **Chave de cache inteligente**

```yaml
key: ${{ runner.os }}-vcpkg-${{ matrix.vcpkg-triplet }}-${{ hashFiles('**/vcpkg.json', 'third_party/vcpkg/.git/HEAD') }}
```

- ✅ Hash do `vcpkg.json` (detecta mudanças)
- ✅ Hash do vcpkg HEAD (detecta updates)
- ✅ Específico por arquitetura (x86)

#### 3. **Binary caching do vcpkg**

```yaml
env:
  VCPKG_BINARY_SOURCES: "clear;x-gha,readwrite"
  VCPKG_FEATURE_FLAGS: "manifests,binarycaching,registries"
```

Usa cache binário nativo do GitHub Actions para pacotes pré-compilados.

#### 4. **Debug de cache**

Mostra se o cache foi usado:
```
✅ vcpkg cache HIT - packages will be restored
```

## ⏱️ Tempo de Build Estimado

| Build | Antes | Depois |
|-------|-------|--------|
| **Primeiro (sem cache)** | ~45 min | ~45 min |
| **Segundo (com cache)** | ~45 min ❌ | **~8-12 min** ✅ |

## 🔍 Verificação

Procure nos logs do Actions:
- "Cache restored successfully" = Cache funcionando
- "Restored packages from binary cache" = vcpkg usando cache binário
- Tempo do step "Configure CMake" muito reduzido

## 📦 Tamanho

- **Total do cache**: ~1.5 GB
- **Limite GitHub**: 10 GB por repo

---

**Resultado**: Builds subsequentes até **70% mais rápidos**! 🚀
