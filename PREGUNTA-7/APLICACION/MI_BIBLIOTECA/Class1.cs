





using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace MI_BIBLIOTECA
{
    public class Class1
    {

        private double c;

        public Class1()
        {
            c = 0;
        }
        public string MultiplicacionImplicita(string expresion)
        {
            for (int i = 0; i < expresion.Length - 1; i++)
            {
                if (char.IsDigit(expresion[i]) && expresion[i + 1] == '(')
                {
                    expresion = expresion.Insert(i + 1, "x"); // Inserta '*' entre el número y '('
                }


            }
            return expresion;
        }
        public bool VerificarParentesisBalanceados(string expresion)
        {
            Stack<char> pila = new Stack<char>();

            foreach (char c in expresion)
            {
                if (c == '(')
                {
                    pila.Push(c);
                }
                else if (c == ')')
                {
                    if (pila.Count == 0)
                    {
                        // Si encontramos un paréntesis de cierre sin uno de apertura, la expresión no es válida
                        return false;
                    }
                    pila.Pop();
                }
            }

            // Si al final la pila no está vacía, significa que faltan paréntesis de cierre
            return pila.Count == 0;
        }

        public bool VerificarSintaxis(string expresion)
        {
            // Eliminar espacios en blanco
            expresion = expresion.Replace(" ", "");

            char[] operadores = { '+', '-', 'x', '/'};

            // Verificar que la expresión no empiece ni termine con un operador
            if (operadores.Contains(expresion[0]) || operadores.Contains(expresion[expresion.Length - 1]))
            {
                return false; // Error de sintaxis
            }

            // Verificar operadores consecutivos
            for (int i = 1; i < expresion.Length; i++)
            {
                if (operadores.Contains(expresion[i]) && operadores.Contains(expresion[i - 1]))
                {
                    return false; // Error de operadores consecutivos
                }
            }

            return true;

        }








        public string ConvertirAPostfija(string expresion)
        {
            Stack<char> operadores = new Stack<char>();
            StringBuilder postfija = new StringBuilder();
            StringBuilder numero = new StringBuilder();

            Dictionary<char, int> precedencia = new Dictionary<char, int>
    {
        { '+', 1 },
        { '-', 1 },
        { 'x', 2 },
        { '/', 2 }
    };

            for (int i = 0; i < expresion.Length; i++)
            {
                char c = expresion[i];

                if (char.IsDigit(c))
                {
                    // Construir el número completo (caso de múltiples dígitos)
                    numero.Append(c);

                    // Si el siguiente carácter no es un dígito, añadimos el número completo
                    if (i == expresion.Length - 1 || !char.IsDigit(expresion[i + 1]))
                    {
                        postfija.Append(numero + " "); // Añadir número a la postfija
                        numero.Clear(); // Reiniciar el StringBuilder del número
                    }
                }
                else if (c == '(')
                {
                    operadores.Push(c);
                }
                else if (c == ')')
                {
                    while (operadores.Count > 0 && operadores.Peek() != '(')
                    {
                        postfija.Append(operadores.Pop() + " ");
                    }
                    operadores.Pop(); // Eliminar el '(' de la pila
                }
                else if (precedencia.ContainsKey(c)) // Si es un operador
                {
                    while (operadores.Count > 0 && operadores.Peek() != '(' &&
                           precedencia[operadores.Peek()] >= precedencia[c])
                    {
                        postfija.Append(operadores.Pop() + " ");
                    }
                    operadores.Push(c);
                }
            }

            // Vaciar los operadores restantes en la pila
            while (operadores.Count > 0)
            {
                postfija.Append(operadores.Pop() + " ");
            }

            return postfija.ToString().Trim();
        }
        public double EvaluarPostfija(string expresionPostfija)
        {
            Stack<double> pila = new Stack<double>();
            string[] tokens = expresionPostfija.Split(' '); // Separar los tokens por espacios

            foreach (string token in tokens)
            {
                if (double.TryParse(token, out double numero)) // Si es un número
                {
                    pila.Push(numero); // Empujar número a la pila
                }
                else // Si es un operador
                {
                    double operando2 = pila.Pop();
                    double operando1 = pila.Pop();

                    switch (token)
                    {
                        case "+":
                            pila.Push(operando1 + operando2);
                            break;
                        case "-":
                            pila.Push(operando1 - operando2);
                            break;
                        case "x":
                            pila.Push(operando1 * operando2);
                            break;
                        case "/":
                            pila.Push(operando1 / operando2);
                            break;
                    }
                }
            }

            return pila.Pop(); // El último elemento en la pila será el resultado final
        }
    }
}
