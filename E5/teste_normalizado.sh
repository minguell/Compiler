#!/bin/bash

# Configurações de pastas
TEST_DIR="test2/test/pass"
MY_OUT_DIR="saidas_teste"
mkdir -p $MY_OUT_DIR

echo "Iniciando testes NORMALIZADOS (Ignorando números de Rótulos/Registradores)..."
echo "------------------------------------------------------------------------"

FAIL_COUNT=0

# Loop por todos os testes (00 a 99)
for i in {00..99}; do
    IN_FILE="$TEST_DIR/pass$i"
    REF_ILOC="$TEST_DIR/pass$i.iloc"
    MY_ILOC="$MY_OUT_DIR/pass$i.iloc"
    
    if [ -f "$IN_FILE" ]; then
        # 1. Gera seu ILOC
        ./etapa5 < "$IN_FILE" > "$MY_ILOC"
        
        # 2. Normaliza o SEU arquivo (r0->REG, L0->LBL)
        # Removemos também espaços em branco extras para evitar falso-positivo
        cat "$MY_ILOC" | sed -E 's/r[0-9]+/REG/g' | sed -E 's/L[0-9]+/LBL/g' | tr -s ' ' > "$MY_ILOC.norm"
        
        # 3. Normaliza o GABARITO
        cat "$REF_ILOC" | sed -E 's/r[0-9]+/REG/g' | sed -E 's/L[0-9]+/LBL/g' | tr -s ' ' > "$REF_ILOC.norm"
        
        # 4. Compara os arquivos normalizados
        # -w ignora espaços em branco, -B ignora linhas em branco
        diff -w -B -q "$MY_ILOC.norm" "$REF_ILOC.norm" > /dev/null
        
        if [ $? -eq 0 ]; then
            echo -e "pass$i: \e[32mOK (Estrutura Idêntica)\e[0m"
        else
            echo -e "pass$i: \e[31mDIFERENTE\e[0m"
            FAIL_COUNT=$((FAIL_COUNT+1))
            
            # Opcional: Se quiser ver o erro do primeiro que falhar, descomente abaixo:
            # echo "--- Diferença (Normalizada) ---"
            # diff -w -B "$MY_ILOC.norm" "$REF_ILOC.norm" | head -n 5
        fi
    fi
done

echo "------------------------------------------------------------------------"
if [ $FAIL_COUNT -eq 0 ]; then
    echo -e "\e[32mSUCESSO TOTAL! A lógica de todos os testes está correta.\e[0m"
else
    echo -e "\e[31m$FAIL_COUNT testes ainda têm diferenças estruturais.\e[0m"
fi