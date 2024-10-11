def fibonacci(n):
    # Verificar si el valor de 'n' es válido
    if n <= 0:
        return "El número debe ser mayor que 0"
    elif n == 1:
        return [0]  # Primer término de Fibonacci
    elif n == 2:
        return [0, 1]  # Primeros dos términos de Fibonacci
    
    # Iniciar los dos primeros términos de la serie
    fib_sequence = [0, 1]
    
    # Calcular los términos restantes
    for i in range(2, n):
        next_term = fib_sequence[-1] + fib_sequence[-2]
        fib_sequence.append(next_term)
    
    return fib_sequence

# Ejemplo: Generar los primeros 10 términos de la secuencia de Fibonacci
n = 10
resultado = fibonacci(n)
print(resultado)