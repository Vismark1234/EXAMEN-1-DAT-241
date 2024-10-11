import multiprocessing as mp
from decimal import Decimal, getcontext

# Ajustar la precisión de los decimales
getcontext().prec = 1000 # Configura la precisión a 100 dígitos (puedes ajustar)

# Función que calcula una porción de la serie de Leibniz con precisión decimal
def leibniz(start, end):
    pi_partial = Decimal(0)
    for i in range(start, end):
        pi_partial += Decimal((-1)**i) / Decimal(2 * i + 1)
    return pi_partial

def calcular_pi(n_terms,num_procesadores):
    # Determinar el número de procesadores
    
    pool = mp.Pool(processes=num_procesadores)

    # Dividir el trabajo entre los procesadores
    rango = n_terms // num_procesadores
    rangos = [(i * rango, (i + 1) * rango) for i in range(num_procesadores)]
    
    #print(rangos)
    # Asignar tareas a los procesos
    resultados = pool.starmap(leibniz, rangos)
    #print(results)
    # Cerrar el pool y esperar a que todos los procesos terminen
    pool.close()
    pool.join()

    # Sumar los resultados parciales y multiplicar por 4 para obtener pi
    pi_estimate = Decimal(4) * sum(resultados)
    return pi_estimate

if __name__ == "__main__":
    n_terms = 1_000_000  # 1 millón de términos
    num_procesadores = 3  # Usar al menos 3 procesadores
    pi = calcular_pi(n_terms,num_procesadores)
    print(f"Estimación de pi usando {n_terms} términos: {pi}")
