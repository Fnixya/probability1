# Para 3 dados cogiendo los 2 mejores y con orden 11, 21, 22, 31, 32, 33...

# generamos las probabilidades con un patrón random que he encontrado
caras = 6
pdf = []
for i in range(caras):
    for ii in range(i):
        pdf.append(3 + 6 * ii)
    pdf.append(1 + 3 * i)
print(pdf)

# cum sum
cdf = []
for i in range(len(pdf)):
    if (i == 0):
        cdf.append(pdf[0])
    else:
        cdf.append(cdf[-1] + pdf[i])

print(cdf)
