caras = 6
for i in range(caras + 1):
    pdf = []
    for ii in range(i):
        for iii in range(ii):
            pdf.append((3 + 6 * iii) / (i**3))
        pdf.append((1 + 3 * ii) / (i**3))

    media = 0
    for ii in range(len(pdf)):
        media = media + (ii + 1) * pdf[ii]
    print(f"media para {i} caras = {media}")
