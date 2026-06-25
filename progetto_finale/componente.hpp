/* creo un nuovo tipo di variabile che può assumere solo questi due valori.
Questo mi aiuta a rendere il codice più leggibile e previene errori che potrebbero
sorgere. */
enum class CompType { Resistor, VoltageSource };

struct Component {
	CompType type;
	int id;               // Es. 1 per R1 o V1
	double value;         // Ohm o Volt
	int original_node1;   // Nodo 1 (Polo + per i generatori)
	int original_node2;   // Nodo 2 (Polo - per i generatori)
};
