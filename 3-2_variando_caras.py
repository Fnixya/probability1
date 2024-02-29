import matplotlib.pyplot as plt
# Para 3 dados cogiendo los 2 mejores y con orden 11, 21, 22, 31, 32, 33...

# generamos las probabilidades con un patrón random que he encontrado
caras = 6
pdf = []
for i in range(caras):
    for ii in range(i):
        pdf.append((3 + 6 * ii) / (caras**3))
    pdf.append((1 + 3 * i) / (caras**3))

# cum sum
cdf = []
for i in range(len(pdf)):
    if (i == 0):
        cdf.append(pdf[0])
    else:
        cdf.append(cdf[-1] + pdf[i])

xaxis = []
for i in range(caras + 1):
    dado1 = ""
    dado1 = dado1 + str(i) + ","
    for ii in range(i):
        dado2 = dado1
        dado2 = dado2 + str(ii + 1) + " "
        xaxis.append(dado2)

plt.bar(xaxis, pdf) # cambiar entre cdf o pdf
plt.show()
