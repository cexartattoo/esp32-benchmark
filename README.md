# 📊 ESP32 Performance Benchmark Analysis

> Análisis completo del rendimiento del ESP32 con diferentes tipos de datos y operaciones

## 🌐 Ver Análisis Online

**[🔗 Ver Análisis Completo](https://tu-usuario.github.io/esp32-benchmark-analysis)**

## 📋 Resumen de Resultados

### 🏆 Mejores Performers
- **uint8_t**: El más rápido para operaciones básicas
- **int8_t**: Muy cercano en rendimiento
- **String concatenación**: Sorprendentemente eficiente
- **Array acceso**: Extremadamente rápido

### ⚠️ Operaciones Costosas
- **double**: 6-10x más lento que float
- **Funciones trigonométricas**: Muy costosas
- **Prints al Serial**: Dominan el tiempo total
- **String reemplazo**: Operación más lenta de strings

## 📊 Resultados Principales

| Tipo de Dato | Multiplicación (μs) | División (μs) | Suma (μs) | Resta (μs) |
|--------------|--------------------:|-------------:|----------:|----------:|
| int8_t       | 62,740             | 112,929      | 58,559    | 96,198    |
| uint8_t      | 62,740             | 102,054      | 58,558    | 58,558    |
| int32_t      | 92,016             | 104,566      | 92,017    | 92,016    |
| float        | 114,721            | 293,421      | 112,971   | -         |
| double       | 700,938            | 2,584,679    | 484,660   | -         |

## 🔧 Código del Benchmark

```cpp
const uint32_t ITER = 1000000;  // Número de iteraciones

template <typename T>
uint32_t benchMul(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 1;
  for (uint32_t i = 0; i < ITER; i++) {
    acc *= a;
    if (acc > 1000) acc = 1;
  }
  (void)acc;
  return micros() - start;
}
```

## 💡 Recomendaciones

1. **Usa int8_t/uint8_t** cuando el rango lo permita
2. **Evita double** en aplicaciones críticas de tiempo
3. **Minimiza los prints al Serial** en bucles críticos
4. **Prefiere float** sobre double para matemáticas

## 🖼️ Capturas del Análisis

### Tabla de Rendimiento

![Benchmark Results](https://github.com/cexartattoo/esp32-benchmark/blob/main/screenshots/results.png)

### Gráfico Comparativo

![Performance Chart](C:\Users\ramir\PycharmProjects\esp32-benchmark\screenshots\O_basicas.png)

### Análisis Detallado

![Detailed Analysis](C:\Users\ramir\PycharmProjects\esp32-benchmark\screenshots\results.png)

## 📁 Estructura del Proyecto

```
esp32-benchmark-analysis/
├── index.html          # Análisis web interactivo
├── benchmark.ino       # Código del benchmark para ESP32
├── README.md          # Este archivo
└── screenshots/       # Capturas de pantalla
    ├── results.png
    ├── chart.png
    └── analysis.png
```

## 🚀 Cómo Usar

1. **Ejecutar Benchmark:**
   ```bash
   # Cargar benchmark.ino en tu ESP32
   # Abrir Serial Monitor a 115200 baudios
   # Copiar resultados
   ```

2. **Ver Análisis:**
   ```bash
   # Abrir index.html en navegador
   # O visitar: https://tu-usuario.github.io/esp32-benchmark-analysis
   ```

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Si tienes ideas para mejorar el benchmark:

1. Fork el proyecto
2. Crea una rama para tu feature
3. Commit tus cambios
4. Push a la rama
5. Abre un Pull Request

## 📄 Licencia

MIT License - ver [LICENSE](LICENSE) para más detalles.

## 🏷️ Tags

`esp32` `benchmark` `performance` `arduino` `embedded` `microcontroller` `analysis`

---

**⭐ Si te gusta este proyecto, dale una estrella!**