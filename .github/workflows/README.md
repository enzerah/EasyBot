# GitHub Actions Workflows

## Build EasyBot

Este workflow compila automaticamente o EasyBot (DLL) a cada push ou pull request.

### Melhorias implementadas:

✅ **Cache inteligente do vcpkg** - Reduz o tempo de build significativamente
✅ **Busca automática do grpc_cpp_plugin** - Não depende de paths hardcoded
✅ **Workflow_dispatch** - Permite executar manualmente pela interface do GitHub
✅ **Artifacts organizados** - Faz upload das DLLs e executáveis compilados

### Executando manualmente:

1. Vá em `Actions` no repositório
2. Selecione `Build EasyBot`
3. Clique em `Run workflow`

### Tempo estimado:

- **Primeira execução**: ~45 minutos (instala dependências)
- **Builds subsequentes**: ~10-15 minutos (usa cache)

### Baixando os binários:

Após o build completar, vá em:
1. `Actions` > Workflow executado
2. Role até o final
3. Clique em `EasyBot-Release` para baixar
