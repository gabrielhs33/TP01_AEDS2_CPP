<h1 align="center">📊 Estruturas de Dados Avançadas em C++</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-%2300599C?style=flat&logo=c%2B%2B&logoColor=white" alt="C++17">
  <img src="https://img.shields.io/badge/Algorithms-Advanced-%2300B4D8" alt="Algoritmos Avançados">
  <img src="https://img.shields.io/badge/Data_Structures-Hash%2FSort-%23FF6D00" alt="Estruturas de Dados">
</p>

<p align="center">Trabalho prático desenvolvido para a disciplina de Algoritmos e Estruturas de Dados 2, implementando três técnicas fundamentais de manipulação de dados.</p>

<h2>📚 Técnicas Implementadas</h2>

<div align="center">
  <table>
    <tr>
      <th>Técnica</th>
      <th>Complexidade</th>
      <th>Arquivo</th>
    </tr>
    <tr>
      <td>Tabela Hashing</td>
      <td>O(1) médio</td>
      <td>hashing.cpp</td>
    </tr>
    <tr>
      <td>Seleção por Substituição</td>
      <td>O(n log k)</td>
      <td>selection.cpp</td>
    </tr>
    <tr>
      <td>Intercalação Ótima</td>
      <td>O(n log n)</td>
      <td>merge.cpp</td>
    </tr>
  </table>
</div>

<h2>📂 Estrutura do Projeto</h2>

<pre>
TP01_AEDS2_CPP/
├── src/
│   ├── hashing/               # Implementação da tabela hash
│   │   ├── hash_table.h       # Interface da tabela
│   │   └── hash_table.cpp     # Implementação
│   │
│   ├── selection/             # Seleção por substituição
│   │   ├── replacement_selection.h
│   │   └── replacement_selection.cpp
│   │
│   ├── merge/                 # Intercalação ótima
│   │   ├── optimal_merge.h
│   │   └── optimal_merge.cpp
│   │
│   ├── utils/                 # Utilitários
│   │   ├── file_utils.h
│   │   └── metrics.h
│   │
│   └── main.cpp               # Programa principal
│
├── data/                     # Arquivos de teste
│   ├── input/
│   └── output/
│
├── Makefile                  # Script de compilação
└── README.md
</pre>

<h2>🔧 Compilação e Execução</h2>

<ol>
  <li>Compilar o projeto:
    <pre><code>make all</code></pre>
  </li>
  <li>Executar o programa principal:
    <pre><code>./bin/tp1 [opções]</code></pre>
  </li>
  <li>Opções de execução:
    <ul>
      <li><code>-h</code>: Modo hashing</li>
      <li><code>-s</code>: Modo seleção por substituição</li>
      <li><code>-m</code>: Modo intercalação ótima</li>
    </ul>
  </li>
</ol>

<h2>📊 Implementação da Tabela Hashing</h2>

<h3>Características:</h3>
<ul>
  <li>Tratamento de colisões por endereçamento aberto</li>
  <li>Função hash modular</li>
  <li>Redimensionamento dinâmico</li>
</ul>

<pre><code>class HashTable {
private:
  struct Entry {
    int key;
    string value;
    bool occupied = false;
  };
  vector&lt;Entry&gt; table;
  int capacity;
  int size;
  
  int hashFunction(int key) {
    return key % capacity;
  }
  
public:
  void insert(int key, string value);
  string search(int key);
  void remove(int key);
};</code></pre>

<h2>⚙️ Seleção por Substituição</h2>

<p>Algoritmo para ordenação externa com memória limitada:</p>

<ol>
  <li>Carrega blocos de dados na memória</li>
  <li>Ordena e escreve blocos ordenados</li>
  <li>Substitui elementos conforme nova entrada</li>
</ol>


<h2>📈 Intercalação Ótima</h2>

<p>Algoritmo de merge de múltiplos caminhos:</p>

<pre><code>void optimalMerge(const vector&lt;string&gt;& input_files, const string& output_file) {
  priority_queue&lt;Node*, vector&lt;Node*&gt;, Compare&gt; min_heap;
  
  // Inicializa heap com primeiro elemento de cada arquivo
  for (auto file : input_files) {
    ifstream input(file);
    if (input >> value) {
      min_heap.push(new Node(value, file));
    }
  }
  
  // Processamento
  while (!min_heap.empty()) {
    Node* min = min_heap.top();
    min_heap.pop();
    output << min->value;
    
    if (input >> min->value) {
      min_heap.push(min);
    }
  }
}</code></pre>

<h2>📊 Métricas de Desempenho</h2>

<table>
  <tr>
    <th>Operação</th>
    <th>Tamanho dos Dados</th>
    <th>Tempo Médio</th>
  </tr>
  <tr>
    <td>Inserção Hash</td>
    <td>10.000 elementos</td>
    <td>~15ms</td>
  </tr>
  <tr>
    <td>Seleção por Substituição</td>
    <td>1MB arquivo</td>
    <td>~120ms</td>
  </tr>
  <tr>
    <td>Intercalação Ótima</td>
    <td>5 arquivos de 500KB</td>
    <td>~350ms</td>
  </tr>
</table>

<h2>📝 Relatório Técnico</h2>

<p>O trabalho inclui análise detalhada de:</p>
<ul>
  <li>Complexidade assintótica de cada algoritmo</li>
  <li>Comparação entre abordagens</li>
  <li>Análise experimental vs teórica</li>
  <li>Limitações e melhorias potenciais</li>
</ul>

<p align="center">
  Desenvolvido por 
  <a href="https://github.com/gabrielhs33">Gabriel Henrique</a>, 
  <a href="https://github.com/Yan-Raniere">Yan Raniere</a> e 
  <a href="https://github.com/MikaelMagal">Mikael Magalhães</a> 
  para AEDS II
</p>
