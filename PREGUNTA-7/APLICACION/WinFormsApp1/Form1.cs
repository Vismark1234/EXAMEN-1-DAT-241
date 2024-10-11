using MI_BIBLIOTECA;
using System.Linq.Expressions;
namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        Class1 c1 = new Class1();
        public Form1()
        {
            InitializeComponent();
        }
        private void button_Click(object sender, EventArgs e)
        {
            string c = (sender as Button)?.Text;
            string nombre_boton = (sender as Button)?.Name;

            // Si se hace clic en el botón 19, realizamos una operación especial y salimos del método
            if (nombre_boton == "button19")
            {
                if (c != "")
                {
                    // Asigna el texto almacenado en button19 al TextBox y limpia button19
                    textBox1.Text = button19.Text;
                    textBox1.SelectionStart = textBox1.Text.Length;
                    textBox1.Focus();
                    button19.Text = "";
                }
                return; // Aquí salimos de la función para evitar la ejecución de más código
            }

            // Limpia el TextBox si el botón "C" es clicado
            if (nombre_boton == "button1")
            {
                textBox1.Text = ""; // Asegúrate de usar una cadena vacía
               
                return;
            }
            if (c == "<--")
            {
                if (textBox1.Text.Length > 0) // Asegúrate de que la cadena no esté vacía
                {
                    textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.Length - 1); // Elimina el último carácter
                }
                return;
            }
            // Si se hace clic en "=" se evalúa la expresión
            if (c == "=")
            {
                string expresion = textBox1.Text;

                expresion = c1.MultiplicacionImplicita(expresion);
                bool val = VerificarExpresion(expresion);

                if (val)
                {
                    try
                    {
                        string expresionPostfija = c1.ConvertirAPostfija(expresion);
                        double resultado = c1.EvaluarPostfija(expresionPostfija);
                        textBox1.Text = resultado.ToString();

                        // Guardar la expresión en button19
                        button19.Text = expresion;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Error: " + ex.Message);
                    }
                }
                textBox1.SelectionStart = expresion.Length;
                textBox1.Focus();
                return;
            }
            else { 
                // Si no es ninguno de los casos anteriores, insertamos el texto en la posición actual del cursor
                int cursorPosition = textBox1.SelectionStart;
                textBox1.Text = textBox1.Text.Insert(cursorPosition, c);
                textBox1.SelectionStart = cursorPosition + c.Length;
                textBox1.Focus();
            }   
        }



        public bool VerificarExpresion(string expresion)
        {

            // Verificar que los paréntesis estén balanceados
            if (!c1.VerificarParentesisBalanceados(expresion))
            {
                MessageBox.Show("Error: Los paréntesis no están balanceados.");
                return false;
            }

            // Verificar la sintaxis general de la expresión
            if (!c1.VerificarSintaxis(expresion))
            {
                MessageBox.Show("Error: Sintaxis incorrecta.");
                return false;
            }

            return true; // La expresión es válida
        }


        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            // Permitir solo números, paréntesis, y los operadores +, -, *, /
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&
                e.KeyChar != '(' && e.KeyChar != ')' &&
                e.KeyChar != '+' && e.KeyChar != '-' &&
                e.KeyChar != '*' && e.KeyChar != '/')
            {
                e.Handled = true;
            }
            if (e.KeyChar == (char)Keys.Enter)
            {
                e.Handled = true;
            }
        }


    }
}
