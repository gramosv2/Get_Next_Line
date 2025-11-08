# 🧠 Ft_printf

> Proyecto de 42 para recrear la función `printf()` de la librería estándar de C.

---

## 📚 ¿Qué son las funciones variádicas?

Las **funciones variádicas** son aquellas que pueden recibir un **número variable de argumentos**.

Por ejemplo:
```c
int suma(int cantidad, ...);
```

En este caso, el número de argumentos después de `cantidad` puede variar.  
Para poder manejar estos argumentos, utilizamos la librería estándar:

```c
#include <stdarg.h>
```

---

## ⚙️ Librería `<stdarg.h>`

Esta librería proporciona las herramientas necesarias para gestionar los argumentos variables.  
A continuación se describen las funciones y macros principales:

| Macro / Tipo | Descripción |
|---------------|-------------|
| **`va_list`** | Tipo de dato usado para declarar una variable que almacena los argumentos. |
| **`va_start(va, argN)`** | Inicializa el acceso a los argumentos. `argN` es el último argumento fijo. |
| **`va_arg(va, tipo)`** | Devuelve el siguiente argumento del tipo indicado. |
| **`va_end(va)`** | Libera los recursos utilizados por `va_list`. |

Ejemplo básico:
```c
#include <stdarg.h>
#include <stdio.h>

int	suma(int cantidad, ...)
{
	va_list	args;
	int		total;
	int		i;

	total = 0;
	i = 0;
	va_start(args, cantidad);
	while (i < cantidad)
	{
		total += va_arg(args, int);
		i++;
	}
	va_end(args);
	return (total);
}

```

---

## 🔄 Flujo de ejecución de `ft_printf`

### 🎯 Propósito
Leer la cadena de formato e imprimir cada carácter hasta encontrar un `%`.  
Cuando se detecta un `%`, se analiza el **especificador de formato** y se imprime el argumento correspondiente.

---

### 🧩 Esquema general

```c
int ft_printf(const char *format, ...)
{
    va_list params;
    int counter = 0;

    va_start(params, format);
    while (*format)
    {
        if (*format != '%')
            counter += ft_putchar(*format);
        else
        {
            format++;
            counter += ft_handle_format(*format, params);
        }
        format++;
    }
    va_end(params);
    return counter;
}
```

---

### 🧠 Flujo paso a paso

1. `ft_printf(*entero, ...)`
2. Inicializamos `counter = 0`
3. `va_start(params, entero)`
4. Bucle mientras exista `*entero`
   - Si `*entero != '%'` → imprimimos el carácter.
   - Si `*entero == '%'`:
     1. Avanzamos el puntero (`entero++`)
     2. Comprobamos el **especificador de formato**
     3. Llamamos a la función correspondiente (ej. `ft_putstr`, `ft_putnbr`, etc.)  
        pasándole el argumento adecuado según el orden recibido.

---

## 🧩 Ejemplo de uso

```c
ft_printf("Hola %s, tienes %d años\n", "Carlos", 27);
```

🖨️ **Salida:**
```
Hola Carlos, tienes 27 años
```

---

## 🧠 Especificadores implementados (ejemplo)

| Especificador | Descripción | Función utilizada |
|----------------|-------------|-------------------|
| `%c` | Carácter | `ft_putchar` |
| `%s` | Cadena | `ft_putstr` |
| `%d` / `%i` | Entero con signo | `ft_putnbr` |
| `%u` | Entero sin signo | `ft_putnbr_unsigned` |
| `%x` / `%X` | Hexadecimal | `ft_puthex` |
| `%p` | Puntero | `ft_putptr` |
| `%%` | Imprime `%` | `ft_putchar('%')` |

---

## 🧰 Estructura del proyecto

```
ft_printf/
├── ft_printf.c
├── ft_printf_utils.c
├── ft_putchar.c
├── ft_putstr.c
├── ft_putnbr.c
├── ft_puthex.c
├── ft_putptr.c
└── Makefile
```
---
## Flujo con ejemplo
```
ft_printf("soy %s %s, tengo %d años\n",Gonzalo,Ramos,27)
		   └├├├├├├├├├├├├├├├├├├├├├├├├─> Camino 1		s
			└├├├├├├├├├├├├├├├├├├├├├├├─> Camino 1		o
	    	 └├├├├├├├├├├├├├├├├├├├├├├─> Camino 1		y
			  └├├├├├├├├├├├├├├├├├├├├├─> Camino 1		' '
			   └├├├├├├├├├├├├├├├├├├├├─> Camino 2.1
				└├├├├├├├├├├├├├├├├├├├─> Camino 2.2	Gonzalo
				 └├├├├├├├├├├├├├├├├├├─> Camino 1		' '
				  └├├├├├├├├├├├├├├├├├─> Camino 2.1
				   └├├├├├├├├├├├├├├├├─> Camino 2.2	Ramos
					└├├├├├├├├├├├├├├├─> Camino 1		,
					 └├├├├├├├├├├├├├├─> Camino 1		' '
					  └├├├├├├├├├├├├├─> Camino 1		t
				       └├├├├├├├├├├├├─> Camino 1		e
						└├├├├├├├├├├├─> Camino 1		n
						 └├├├├├├├├├├─> Camino 1		g
						  └├├├├├├├├├─> Camino 1		o
						   └├├├├├├├├─> Camino 1		' '
							└├├├├├├├─> Camino 2.1
							 └├├├├├├─> Camino 2.2	27
							  └├├├├├─> Camino 1		' '
							   └├├├├─> Camino 1		a
								└├├├─> Camino 1		ñ
								 └├├─> Camino 1		o
								  └├─> Camino 1		s
								   └─> Camino 1		'\n'
├── ft_putstr.c
├── ft_putnbr.c
├── ft_puthex.c
├── ft_putptr.c
└── Makefile
```
---

## 🧾 Créditos

Proyecto desarrollado como parte del **currículum de 42**.  
Autor: *goramos-* 👨‍💻  
Lenguaje: **C**  
Norma: **Norminette compliant**
