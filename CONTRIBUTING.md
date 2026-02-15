# Guia de Contribuição - EasyBot

Obrigado por considerar contribuir para o EasyBot! 🎉

## 🚦 Processo de Desenvolvimento

### 1. Fork e Clone

```bash
git clone https://github.com/SEU-USUARIO/EasyBot.git
cd EasyBot
git submodule update --init --recursive
```

### 2. Crie uma Branch

```bash
git checkout -b feature/minha-funcionalidade
# ou
git checkout -b fix/correcao-bug
```

### 3. Faça suas mudanças

- Mantenha o código limpo e bem documentado
- Siga o estilo de código existente
- Adicione comentários onde necessário

### 4. Teste localmente

```powershell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### 5. Commit

Use mensagens descritivas:

```bash
git commit -m "feat: adiciona suporte a novo comando"
git commit -m "fix: corrige memory leak no EventDispatcher"
git commit -m "docs: atualiza README com exemplos"
```

### Convenção de commits:

- `feat:` Nova funcionalidade
- `fix:` Correção de bug
- `docs:` Mudanças na documentação
- `refactor:` Refatoração de código
- `test:` Adição ou modificação de testes
- `chore:` Tarefas de manutenção

### 6. Push e Pull Request

```bash
git push origin feature/minha-funcionalidade
```

Abra um Pull Request no GitHub com:
- Descrição clara do que foi feito
- Referência a issues relacionadas (se houver)
- Screenshots/logs se aplicável

## 📋 Checklist antes do PR

- [ ] Código compila sem erros
- [ ] Sem warnings do compilador
- [ ] Testado localmente
- [ ] Documentação atualizada (se necessário)
- [ ] Commit messages seguem convenção
- [ ] Não há arquivos desnecessários (build artifacts, etc)

## 🔍 Code Review

Seu PR será revisado considerando:
- Qualidade do código
- Performance
- Segurança
- Compatibilidade
- Documentação

## 🐛 Reportando Bugs

Abra uma issue com:
- Descrição clara do problema
- Passos para reproduzir
- Comportamento esperado vs atual
- Versão do Windows/Visual Studio
- Logs relevantes

## 💡 Sugestões

Issues para sugestões de features são bem-vindas!
Descreva:
- Caso de uso
- Benefícios
- Possível implementação

## 📞 Dúvidas?

Abra uma issue com a tag `question` ou entre em contato com os mantenedores.

---

**Código de Conduta**: Seja respeitoso e profissional em todas as interações.
