#!/bin/bash

# 1. Gera o seu arquivo
./etapa5 < test2/test/pass/pass06 > meu.iloc

# 2. Pega o arquivo de referência
REF="test2/test/pass/pass06.iloc"

# 3. Normaliza ambos (substitui r0..r99 por R_X e L0..L99 por L_X)
#    Remove espaços extras também (-w no diff já faz isso, mas o sed ajuda)
cat meu.iloc | sed -E 's/r[0-9]+/R_X/g' | sed -E 's/L[0-9]+/L_X/g' > meu_norm.txt
cat $REF     | sed -E 's/r[0-9]+/R_X/g' | sed -E 's/L[0-9]+/L_X/g' > ref_norm.txt

# 4. Compara os normalizados
diff -w meu_norm.txt ref_norm.txt