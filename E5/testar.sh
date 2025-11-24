#!/bin/bash

# Caminho onde estão os testes
TEST_DIR="test2/test/pass"
# Pasta para salvar as saídas do seu compilador (para organização)
OUT_DIR="saidas_teste"

mkdir -p $OUT_DIR
echo "Iniciando bateria de testes..."
echo "--------------------------------"

# Contador de erros
FAIL_COUNT=0

# Loop de 00 a 99
for i in {00..99}; do
    # Nome do arquivo fonte (ex: pass05)
    IN_FILE="$TEST_DIR/pass$i"
    # Nome do gabarito esperado (ex: pass05.iloc)
    REF_FILE="$TEST_DIR/pass$i.iloc"
    # Onde salvar sua saída
    MY_OUT="$OUT_DIR/pass$i.iloc"

    # Verifica se o arquivo de teste existe (para evitar erro se pular algum número)
    if [ -f "$IN_FILE" ]; then
        
        # 1. Executa seu compilador
        ./etapa5 < "$IN_FILE" > "$MY_OUT"
        
        # 2. Compara sua saída com o gabarito
        # -w ignora espaços em branco, -q para modo silencioso
        diff -w -q "$MY_OUT" "$REF_FILE" > /dev/null
        
        # Verifica o resultado do diff (0 = igual, 1 = diferente)
        if [ $? -eq 0 ]; then
            echo -e "pass$i: \e[32mOK\e[0m"
        else
            echo -e "pass$i: \e[31mDIFERENTE\e[0m"
            FAIL_COUNT=$((FAIL_COUNT+1))
            # Opcional: Mostra a diferença imediatamente (descomente a linha abaixo se quiser)
            # diff -w "$MY_OUT" "$REF_FILE" | head -n 5
        fi
    fi
done

echo "--------------------------------"
if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "\e[32mTODOS OS TESTES PASSARAM!\e[0m"
else
    echo -e "\e[31m$FAIL_COUNT TESTES FALHARAM.\e[0m Verifique a pasta '$OUT_DIR'."
fi