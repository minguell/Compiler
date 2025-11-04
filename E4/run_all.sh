#!/bin/bash

# O nome do seu compilador, conforme definido no Makefile 
EXECUTABLE="./etapa4"
# O diretório onde os arquivos de teste estão
TEST_DIR="Testes"

# 1. Verifica se o diretório de testes existe
if [ ! -d "$TEST_DIR" ]; then
    echo "Erro: O diretório '$TEST_DIR' não foi encontrado."
    exit 1
fi

# 2. Verifica se o executável existe
if [ ! -f "$EXECUTABLE" ]; then
    echo "Erro: O executável '$EXECUTABLE' não foi encontrado."
    echo "Por favor, compile o projeto primeiro usando 'make'."
    exit 1
fi

echo "Iniciando a execução dos testes no diretório: $TEST_DIR"
echo "Usando o executável: $EXECUTABLE"
echo ""

# 3. Itera por todos os arquivos dentro do diretório TEST_DIR
for test_file in "$TEST_DIR"/*
do
    # Verifica se é realmente um arquivo (e não um subdiretório)
    if [ -f "$test_file" ]; then
        echo "================================================="
        echo "EXECUTANDO: $test_file"
        echo "================================================="
        
        # 4. Executa o compilador e redireciona o conteúdo do arquivo 
        #    de teste para a entrada padrão (stdin) do executável.
        #    As saídas (stdout e stderr) serão impressas no terminal.
        "$EXECUTABLE" < "$test_file"
        
        echo "-------------------------------------------------"
        echo "FINALIZADO: $test_file (Código de saída: $?)"
        echo ""
    fi
done

echo "Todos os testes foram concluídos."