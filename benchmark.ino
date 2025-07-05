const uint32_t ITER = 1000000;  // Número de iteraciones para la prueba
const uint32_t ITER_STRING = 10000;  // Menos iteraciones para strings (son más lentos)
const uint32_t ITER_PRINT = 1000;    // Aún menos para prints

// =============================================================================
// TEMPLATES PARA OPERACIONES ARITMÉTICAS
// =============================================================================

template <typename T>
uint32_t benchMul(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 1;
  for (uint32_t i = 0; i < ITER; i++) {
    acc *= a;
    if (acc > 1000) acc = 1; // Evitar overflow
  }
  (void)acc;
  return micros() - start;
}

template <typename T>
uint32_t benchDiv(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 1000;
  for (uint32_t i = 0; i < ITER; i++) {
    acc /= a;
    if (acc < 1) acc = 1000; // Evitar underflow
  }
  (void)acc;
  return micros() - start;
}

template <typename T>
uint32_t benchAdd(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 0;
  for (uint32_t i = 0; i < ITER; i++) {
    acc += a;
    if (acc > 1000) acc = 0; // Evitar overflow
  }
  (void)acc;
  return micros() - start;
}

template <typename T>
uint32_t benchSub(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 1000;
  for (uint32_t i = 0; i < ITER; i++) {
    acc -= a;
    if (acc < 0) acc = 1000; // Evitar underflow
  }
  (void)acc;
  return micros() - start;
}

template <typename T>
uint32_t benchMod(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 100;
  for (uint32_t i = 0; i < ITER; i++) {
    acc = acc % a;
    if (acc == 0) acc = 100; // Evitar división por cero
  }
  (void)acc;
  return micros() - start;
}

template <typename T>
uint32_t benchMixed(T a, T b) {
  uint32_t start = micros();
  volatile T acc = 10;
  for (uint32_t i = 0; i < ITER; i++) {
    acc = acc * a;
    acc = acc / b;
    acc = acc + a;
    acc = acc - b;
    if (acc > 1000) acc = 10;
    if (acc < 1) acc = 10;
  }
  (void)acc;
  return micros() - start;
}

// =============================================================================
// BENCHMARKS DE PUNTO FLOTANTE
// =============================================================================

uint32_t benchFloatMath() {
  uint32_t start = micros();
  volatile float acc = 1.0;
  for (uint32_t i = 0; i < ITER; i++) {
    acc = acc * 1.1;
    acc = acc / 1.05;
    acc = sin(acc);
    acc = cos(acc);
    acc = sqrt(abs(acc));
    if (acc > 100.0) acc = 1.0;
  }
  (void)acc;
  return micros() - start;
}

uint32_t benchDoubleMath() {
  uint32_t start = micros();
  volatile double acc = 1.0;
  for (uint32_t i = 0; i < ITER; i++) {
    acc = acc * 1.1;
    acc = acc / 1.05;
    acc = sin(acc);
    acc = cos(acc);
    acc = sqrt(abs(acc));
    if (acc > 100.0) acc = 1.0;
  }
  (void)acc;
  return micros() - start;
}

// =============================================================================
// BENCHMARKS DE STRINGS
// =============================================================================

uint32_t benchStringConcat() {
  uint32_t start = micros();
  String str = "Hello";
  for (uint32_t i = 0; i < ITER_STRING; i++) {
    str += " World";
    if (str.length() > 100) str = "Hello";
  }
  return micros() - start;
}

uint32_t benchStringSearch() {
  uint32_t start = micros();
  String str = "The quick brown fox jumps over the lazy dog";
  volatile int pos = 0;
  for (uint32_t i = 0; i < ITER_STRING; i++) {
    pos = str.indexOf("fox");
    pos = str.indexOf("dog");
    pos = str.indexOf("cat"); // No encontrado
  }
  (void)pos;
  return micros() - start;
}

uint32_t benchStringReplace() {
  uint32_t start = micros();
  String str = "Hello World Hello Universe";
  for (uint32_t i = 0; i < ITER_STRING; i++) {
    str.replace("Hello", "Hi");
    str.replace("Hi", "Hello");
  }
  return micros() - start;
}

// =============================================================================
// BENCHMARKS DE ARRAYS
// =============================================================================

uint32_t benchArrayAccess() {
  uint32_t start = micros();
  int arr[100];
  for (int i = 0; i < 100; i++) arr[i] = i;

  volatile int sum = 0;
  for (uint32_t i = 0; i < ITER; i++) {
    sum += arr[i % 100];
  }
  (void)sum;
  return micros() - start;
}

uint32_t benchArraySort() {
  uint32_t start = micros();
  int arr[50];

  for (uint32_t i = 0; i < ITER_STRING; i++) {
    // Llenar array con números aleatorios
    for (int j = 0; j < 50; j++) {
      arr[j] = random(1000);
    }

    // Bubble sort simple
    for (int j = 0; j < 49; j++) {
      for (int k = 0; k < 49-j; k++) {
        if (arr[k] > arr[k+1]) {
          int temp = arr[k];
          arr[k] = arr[k+1];
          arr[k+1] = temp;
        }
      }
    }
  }
  return micros() - start;
}

// =============================================================================
// BENCHMARKS DE PRINTS
// =============================================================================

uint32_t benchPrintInt() {
  uint32_t start = micros();
  for (uint32_t i = 0; i < ITER_PRINT; i++) {
    Serial.print(i);
    Serial.print(" ");
  }
  Serial.println();
  return micros() - start;
}

uint32_t benchPrintFloat() {
  uint32_t start = micros();
  float val = 3.14159;
  for (uint32_t i = 0; i < ITER_PRINT; i++) {
    Serial.print(val, 4);
    Serial.print(" ");
    val += 0.1;
  }
  Serial.println();
  return micros() - start;
}

uint32_t benchPrintString() {
  uint32_t start = micros();
  String str = "Test";
  for (uint32_t i = 0; i < ITER_PRINT; i++) {
    Serial.print(str);
    Serial.print(i);
    Serial.print(" ");
  }
  Serial.println();
  return micros() - start;
}

// =============================================================================
// FUNCIÓN PRINCIPAL DE BENCHMARK
// =============================================================================

void runBenchmark() {
  Serial.println("=================================================");
  Serial.println("          ESP32 BENCHMARK COMPLETO              ");
  Serial.println("=================================================");
  Serial.printf("Iteraciones: %u (aritméticas), %u (strings), %u (prints)\n",
                ITER, ITER_STRING, ITER_PRINT);
  Serial.println();

  // Valores de prueba
  int8_t a8 = 3, b8 = 2;
  int16_t a16 = 300, b16 = 200;
  int32_t a32 = 30000, b32 = 20000;
  uint8_t ua8 = 3, ub8 = 2;
  uint16_t ua16 = 300, ub16 = 200;
  uint32_t ua32 = 30000, ub32 = 20000;
  float af = 3.14, bf = 2.71;
  double ad = 3.14159, bd = 2.71828;

  // =============================================================================
  // BENCHMARK: MULTIPLICACIONES
  // =============================================================================
  Serial.println(">>> MULTIPLICACIONES <<<");
  Serial.printf("int8_t    : %8u us\n", benchMul<int8_t>(a8, b8));
  Serial.printf("int16_t   : %8u us\n", benchMul<int16_t>(a16, b16));
  Serial.printf("int32_t   : %8u us\n", benchMul<int32_t>(a32, b32));
  Serial.printf("uint8_t   : %8u us\n", benchMul<uint8_t>(ua8, ub8));
  Serial.printf("uint16_t  : %8u us\n", benchMul<uint16_t>(ua16, ub16));
  Serial.printf("uint32_t  : %8u us\n", benchMul<uint32_t>(ua32, ub32));
  Serial.printf("float     : %8u us\n", benchMul<float>(af, bf));
  Serial.printf("double    : %8u us\n", benchMul<double>(ad, bd));
  Serial.println();

  // =============================================================================
  // BENCHMARK: DIVISIONES
  // =============================================================================
  Serial.println(">>> DIVISIONES <<<");
  Serial.printf("int8_t    : %8u us\n", benchDiv<int8_t>(a8, b8));
  Serial.printf("int16_t   : %8u us\n", benchDiv<int16_t>(a16, b16));
  Serial.printf("int32_t   : %8u us\n", benchDiv<int32_t>(a32, b32));
  Serial.printf("uint8_t   : %8u us\n", benchDiv<uint8_t>(ua8, ub8));
  Serial.printf("uint16_t  : %8u us\n", benchDiv<uint16_t>(ua16, ub16));
  Serial.printf("uint32_t  : %8u us\n", benchDiv<uint32_t>(ua32, ub32));
  Serial.printf("float     : %8u us\n", benchDiv<float>(af, bf));
  Serial.printf("double    : %8u us\n", benchDiv<double>(ad, bd));
  Serial.println();

  // =============================================================================
  // BENCHMARK: SUMAS
  // =============================================================================
  Serial.println(">>> SUMAS <<<");
  Serial.printf("int8_t    : %8u us\n", benchAdd<int8_t>(a8, b8));
  Serial.printf("int16_t   : %8u us\n", benchAdd<int16_t>(a16, b16));
  Serial.printf("int32_t   : %8u us\n", benchAdd<int32_t>(a32, b32));
  Serial.printf("uint8_t   : %8u us\n", benchAdd<uint8_t>(ua8, ub8));
  Serial.printf("uint16_t  : %8u us\n", benchAdd<uint16_t>(ua16, ub16));
  Serial.printf("uint32_t  : %8u us\n", benchAdd<uint32_t>(ua32, ub32));
  Serial.printf("float     : %8u us\n", benchAdd<float>(af, bf));
  Serial.printf("double    : %8u us\n", benchAdd<double>(ad, bd));
  Serial.println();

  // =============================================================================
  // BENCHMARK: RESTAS
  // =============================================================================
  Serial.println(">>> RESTAS <<<");
  Serial.printf("int8_t    : %8u us\n", benchSub<int8_t>(a8, b8));
  Serial.printf("int16_t   : %8u us\n", benchSub<int16_t>(a16, b16));
  Serial.printf("int32_t   : %8u us\n", benchSub<int32_t>(a32, b32));
  Serial.printf("uint8_t   : %8u us\n", benchSub<uint8_t>(ua8, ub8));
  Serial.printf("uint16_t  : %8u us\n", benchSub<uint16_t>(ua16, ub16));
  Serial.printf("uint32_t  : %8u us\n", benchSub<uint32_t>(ua32, ub32));
  Serial.printf("float     : %8u us\n", benchSub<float>(af, bf));
  Serial.printf("double    : %8u us\n", benchSub<double>(ad, bd));
  Serial.println();

  // =============================================================================
  // BENCHMARK: MÓDULO
  // =============================================================================
  Serial.println(">>> MÓDULO <<<");
  Serial.printf("int8_t    : %8u us\n", benchMod<int8_t>(a8, b8));
  Serial.printf("int16_t   : %8u us\n", benchMod<int16_t>(a16, b16));
  Serial.printf("int32_t   : %8u us\n", benchMod<int32_t>(a32, b32));
  Serial.printf("uint8_t   : %8u us\n", benchMod<uint8_t>(ua8, ub8));
  Serial.printf("uint16_t  : %8u us\n", benchMod<uint16_t>(ua16, ub16));
  Serial.printf("uint32_t  : %8u us\n", benchMod<uint32_t>(ua32, ub32));
  Serial.println();

  // =============================================================================
  // BENCHMARK: OPERACIONES MIXTAS
  // =============================================================================
  Serial.println(">>> OPERACIONES MIXTAS (mul+div+add+sub por ciclo) <<<");
  Serial.printf("int8_t    : %8u us\n", benchMixed<int8_t>(a8, b8));
  Serial.printf("int16_t   : %8u us\n", benchMixed<int16_t>(a16, b16));
  Serial.printf("int32_t   : %8u us\n", benchMixed<int32_t>(a32, b32));
  Serial.printf("uint8_t   : %8u us\n", benchMixed<uint8_t>(ua8, ub8));
  Serial.printf("uint16_t  : %8u us\n", benchMixed<uint16_t>(ua16, ub16));
  Serial.printf("uint32_t  : %8u us\n", benchMixed<uint32_t>(ua32, ub32));
  Serial.printf("float     : %8u us\n", benchMixed<float>(af, bf));
  Serial.printf("double    : %8u us\n", benchMixed<double>(ad, bd));
  Serial.println();

  // =============================================================================
  // BENCHMARK: MATEMÁTICAS AVANZADAS
  // =============================================================================
  Serial.println(">>> MATEMÁTICAS AVANZADAS (sin, cos, sqrt) <<<");
  Serial.printf("float     : %8u us\n", benchFloatMath());
  Serial.printf("double    : %8u us\n", benchDoubleMath());
  Serial.println();

  // =============================================================================
  // BENCHMARK: STRINGS
  // =============================================================================
  Serial.println(">>> STRINGS <<<");
  Serial.printf("Concatenación : %8u us\n", benchStringConcat());
  Serial.printf("Búsqueda      : %8u us\n", benchStringSearch());
  Serial.printf("Reemplazo     : %8u us\n", benchStringReplace());
  Serial.println();

  // =============================================================================
  // BENCHMARK: ARRAYS
  // =============================================================================
  Serial.println(">>> ARRAYS <<<");
  Serial.printf("Acceso        : %8u us\n", benchArrayAccess());
  Serial.printf("Ordenamiento  : %8u us\n", benchArraySort());
  Serial.println();

  // =============================================================================
  // BENCHMARK: PRINTS AL SERIAL
  // =============================================================================
  Serial.println(">>> PRINTS AL SERIAL <<<");
  Serial.printf("Enteros       : %8u us\n", benchPrintInt());
  Serial.printf("Flotantes     : %8u us\n", benchPrintFloat());
  Serial.printf("Strings       : %8u us\n", benchPrintString());
  Serial.println();

  Serial.println("=================================================");
  Serial.println("            BENCHMARK COMPLETADO                ");
  Serial.println("=================================================");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Iniciando benchmark en 3 segundos...");
  delay(3000);

  runBenchmark();
}

void loop() {
  // Repetir benchmark cada 30 segundos
  delay(30000);
  Serial.println("\n--- EJECUTANDO BENCHMARK NUEVAMENTE ---\n");
  runBenchmark();
}