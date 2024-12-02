# 🌱 Sistema de Gestão de Hortifruti

Bem-vindo ao sistema de gestão de hortifruti! Este software foi desenvolvido para facilitar o gerenciamento de produtos, vendas, compras, doações e estoque em um ambiente comercial de hortifruti.

---

## 🚀 Funcionalidades

### 📊 Dashboard
- Exibe informações gerais sobre vendas, produtos mais vendidos e estoque.
- Permite monitoramento financeiro, com cálculos de receita, custo e lucro.

### 🛒 Gestão de Produtos
- Cadastro de novos produtos com informações detalhadas como nome, tipo, validade e valor nutricional.
- Atualização de estoque com base em compras e vendas realizadas.

### 🧾 Vendas e Compras
- Registro de vendas e compras com controle de quantidade e valores.
- Cálculo automático de taxas de frete para vendas online.

### 🤝 Doações
- Gerenciamento de doações de produtos, com atualização automática do estoque.

### 👥 Cadastro de Funcionários
- Cadastro de funcionários com geração de IDs únicos.
- Salvamento seguro de credenciais no formato CSV.

---

## 🛠 Estrutura do Projeto

O projeto é estruturado em diversos módulos para facilitar a manutenção e expansão:

- **dashboard.c**: Exibição do painel de controle.
- **venda.c**: Operações relacionadas a vendas.
- **compra.c**: Gestão de compras.
- **doacao.c**: Gerenciamento de doações.
- **cadastrar_produto.c**: Cadastro de produtos no sistema.
- **cadastrar_funcionario.c**: Cadastro de novos funcionários.
- **utils.h**: Funções utilitárias para manipulação de interface e entradas.
- **ascii.c**: Arte ASCII para melhorar a experiência visual.

---

## 🗂 Estrutura de Dados

### 📦 Arquivos CSV
Os dados são armazenados em arquivos CSV para facilitar a integração e análise externa:
- `produtos.csv`: Informações sobre os produtos.
- `registro_vendas.csv`: Registro de todas as vendas, compras e doações.
- `credenciais_funcionarios.csv`: Dados dos funcionários cadastrados.

### 📑 Estruturas
O sistema utiliza as seguintes estruturas principais:
- **Produto**: Representa os itens disponíveis no hortifruti.
- **Venda**: Armazena informações sobre vendas realizadas.
- **ProdutoCompra**: Relaciona produtos e suas quantidades.

---

## ⚙️ Tecnologias Utilizadas
- **Linguagem**: C
- **Interface**: Console (CLI)
- **Sistema Operacional**: Windows (compatível com comandos do sistema como `cls`)

---

## 🛡 Segurança
- Armazenamento seguro das credenciais dos funcionários.
- Controle de acesso a funcionalidades administrativas.

---

## 🎨 Experiência do Usuário
O sistema oferece uma interface visual agradável com:
- **Arte ASCII** para criar um ambiente amigável.
- **Menus intuitivos** com navegação fácil através de teclas.

---

## 📋 Requisitos do Sistema
- **Compilador C**: Compatível com bibliotecas padrão.
- **Windows**: Para suporte aos comandos e bibliotecas específicas.

---

## 🏁 Como Executar

1. **Clonar o Repositório**:
   ```bash
   git clone https://github.com/LuigiNeto01/Pim-2-Semestre.git
   ```
## 🏁 Como Executar

### Compilar o Sistema:
```bash
gcc -o sistema.exe main.c
```

#Executar:
```bash
sistema
```
---

