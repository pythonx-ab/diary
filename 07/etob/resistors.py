

def resistor_divider(vin, r1, r2):
    return vin * r2 / (r1 + r2)

#export = resistor_divider