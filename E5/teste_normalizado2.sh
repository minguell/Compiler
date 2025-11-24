#!/bin/bash

# Configurações
FAIL_DIR="test2/test/fail"
echo "Iniciando testes da pasta FAIL..."
echo "------------------------------------------------------------------------"

SUCCESS_COUNT=0
FAIL_COUNT=0

# Percorre todos os arquivos na pasta fail
for file in "$FAIL_DIR"/*; do
    # Pega apenas o nome do arquivo (ex: fail01)
    test_name=$(basename "$file")
    
    # Executa o compilador descartando a saída padrão (stdout) e de erro (stderr)
    # Queremos apenas saber o código de retorno ($?)
    ./etapa5 < "$file" > /dev/null 2>&1
    
    RET_CODE=$?

    # Se o código de retorno for DIFERENTE de 0, o compilador identificou o erro (Correto)
    if [ $RET_CODE -ne 0 ]; then
        # Verifica se foi Segmentation Fault (código 139 geralmente)
        if [ $RET_CODE -eq 139 ]; then
             echo -e "$test_name: \e[31mFALHOU (Segmentation Fault / Crash)\e[0m"
             FAIL_COUNT=$((FAIL_COUNT+1))
        else
             echo -e "$test_name: \e[32mOK (Erro detectado: $RET_CODE)\e[0m"
             SUCCESS_COUNT=$((SUCCESS_COUNT+1))
        fi
    else
        # Se retornou 0, o compilador aceitou um programa inválido (Erro)
        echo -e "$test_name: \e[31mFALHOU (Aceitou código inválido)\e[0m"
        FAIL_COUNT=$((FAIL_COUNT+1))
    fi
done

echo "------------------------------------------------------------------------"
echo -e "Testes que passaram (detectaram erro): \e[32m$SUCCESS_COUNT\e[0m"
echo -e "Testes que falharam (aceitaram ou crasharam): \e[31m$FAIL_COUNT\e[0m"