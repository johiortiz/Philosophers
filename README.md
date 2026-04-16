# Philosophers

*Este proyecto ha sido creado como parte del currículo de 42 por johiortiz.*

## Descripción

**Philosophers** es un proyecto clásico de concurrencia basado en el problema de los *filósofos comensales* (Dining Philosophers). El objetivo es diseñar y programar una simulación con múltiples hilos/procesos donde varios filósofos alternan entre pensar, comer y dormir, compartiendo recursos limitados (tenedores) sin caer en **interbloqueo (deadlock)**, **inanición (starvation)** ni condiciones de carrera.

En este repositorio encontrarás una implementación en **C** (con compilación mediante **Makefile**) que pone en práctica:

- Sincronización con primitivas (por ejemplo, mutex/semáforos según la versión del proyecto).
- Gestión correcta del tiempo y estados del sistema.
- Manejo de errores y liberación de recursos.

## Instrucciones


### Requisitos

- `gcc` o `clang`
- `make`
- (Linux/macOS) soporte de hilos (p. ej. `pthread`)

### Compilación

```bash
make
```

Para limpiar archivos generados:

```bash
make clean
make fclean
```

### Ejecución

Normalmente el programa se ejecuta indicando parámetros como:

- número de filósofos
- `time_to_die`
- `time_to_eat`
- `time_to_sleep`
- (opcional) número de veces que cada filósofo debe comer

Ejemplo típico:

```bash
./philo 5 800 200 200
```

Con número mínimo de comidas:

```bash
./philo 5 800 200 200 7
```

Si tu repositorio incluye la versión *bonus*:

```bash
make bonus
./philo_bonus 5 800 200 200
```

## Recursos

### Referencias sobre concurrencia y el problema de los filósofos

- E. W. Dijkstra — *The Dining Philosophers Problem* (planteamiento clásico del problema).
- Documentación POSIX Threads (pthreads): mutexes, threads y sincronización.
- Semáforos POSIX (`sem_*`) (útil para implementaciones basadas en procesos).
- *Operating Systems: Three Easy Pieces (OSTEP)* — capítulos de concurrencia y sincronización.
- Artículos/guías sobre deadlock, starvation y estrategias de prevención (orden de recursos, jerarquía de locks, etc.).

### Uso de IA

Este proyecto **puede haberse apoyado en herramientas de IA** para tareas puntuales como:

- Revisión del formato del README y redacción (documentación).
- Recordatorio/consulta de conceptos teóricos de concurrencia (deadlock/starvation) y prácticas recomendadas.

**No se ha utilizado IA** para generar automáticamente la lógica central del programa (sincronización/algoritmo) ni para escribir código fuente de producción sin revisión; cualquier sugerencia se ha validado manualmente mediante pruebas y lectura del código.

---
