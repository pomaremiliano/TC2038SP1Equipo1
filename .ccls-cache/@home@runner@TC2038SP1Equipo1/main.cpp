/*
Actividad Integradora 1

Integrantes:
Jorge Emiliano Pomar Mendoza | A01709338
Eliuth Balderas Neri | A01703315
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string leerArchivo(std::string nombreArchivo) {
  std::ifstream archivo(nombreArchivo);
  std::string contenido((std::istreambuf_iterator<char>(archivo)),
                        std::istreambuf_iterator<char>());
  return contenido;
}

void construyeArregloLPS(const std::string &secuencia, int m,
                         std::vector<int> &lps) {
  int len = 0; // longitud de la secuencia previa mas larga
  int i = 1;   // indice de la secuencia

  lps[0] = 0; // inicializamos lps[0] = 0 porque no hay ninguna secuencia previa
              // mas larga

  while (i < m) { // recorremos la secuencia
    if (secuencia[i] ==
        secuencia[len]) { // si la secuencia en la posicion i es igual a la
      // secuencia en la posicion len entonces incrementamos
      // len y lps[i] = len
      len++;
      lps[i] = len;
      i++;
    } else { // si no son iguales
      if (len != 0) {
        len = lps[len - 1];
      } else { // si len es 0 entonces lps[i] = 0 e incrementamos i
        lps[i] = 0;
        i++;
      }
    }

    if (i < m && len > 0) {
      lps[len] = len;
    }
  }
}

int buscaSecuencia(
    const std::string &contenido,
    const std::string &secuencia) { // Procesa el patron y busca en el archivo
  // usando algoritmo KMP O(m + n)
  int n = contenido.length();
  int m = secuencia.length();
  std::vector<int> lps(m, 0);
  construyeArregloLPS(secuencia, m, lps);

  int i = 0;
  int j = 0;

  while (i < n) {
    if (secuencia[j] == contenido[i]) {
      j++;
      i++;
    }

    if (j == m) {
      return i - j;
    } else if (i < n && secuencia[j] != contenido[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i = i + 1;
      }
    }
  }

  return -1;
}
#include <chrono>

int encuentraPalindromoManacher(
    const std::string &contenido) { // Implementacion de Manacher O(n) para
  // encontrar palindromos
  std::string secuencia = "$#";
  for (const auto &c : contenido) {
    secuencia += c;
    secuencia += "#";
  }
  secuencia += "@";
  int n = secuencia.length();
  std::vector<int> lps(n, 0);
  int c = 0, r = 0;
  for (int i = 1; i < n - 1; i++) {
    int mirr = 2 * c - i;
    if (i < r) {
      lps[i] = std::min(r - i, lps[mirr]);
    }
    while (secuencia[i + (1 + lps[i])] == secuencia[i - (1 + lps[i])]) {
      lps[i]++;
    }
    if (i + lps[i] > r) {
      c = i;
      r = i + lps[i];
    }
  }
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n - 1; i++) {
    if (lps[i] > maxLen) {
      maxLen = lps[i];
      centerIndex = i;
    }
  }
  return maxLen;
}
// Referencia: https://cp-algorithms.com/string/manacher.html

int encuentraPalindromoBruto(
    const std::string &contenido) { // Implementacion de busqueda bruta O(n^3)
  // para encontrar palindromos
  int n = contenido.length();
  int maxLen = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      bool esPalindromo = true;
      for (int k = i; k <= (i + j) / 2; k++) {
        if (contenido[k] != contenido[j - (k - i)]) {
          esPalindromo = false;
          break;
        }
      }
      if (esPalindromo) {
        maxLen = std::max(maxLen, j - i + 1);
      }
    }
  }
  return maxLen;
}
// basado en https://www.tamps.cinvestav.mx/~ertello/algorithms/sesion07.pdf

int encuentraSubMasLargo(const std::string &contenido) {
  int n = contenido.length();
  int maxLen = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (contenido[i] == contenido[j]) {
        int len = 0;
        int k = i;
        while (k < n && contenido[k] == contenido[j]) {
          len++;
          k++;
          j++;
        }
        maxLen = std::max(maxLen, len);
      }
    }
  }
  return maxLen;
}

int main() {
  std::vector<std::string> nombresTransmision = {
      "Situacion_Problema_1/transmission01.txt",
      "Situacion_Problema_1/transmission02.txt",
  };

  std::vector<std::string> secuencias = {
      leerArchivo("Situacion_Problema_1/mcode01.txt"),
      leerArchivo("Situacion_Problema_1/mcode02.txt"),
      leerArchivo("Situacion_Problema_1/mcode03.txt"),
  };

  // busca codigos maliciosos
  std::cout << "\n////// Parte 1 //////" << std::endl;
  for (const auto &nombreArchivo : nombresTransmision) {
    std::string contenidoTransmision = leerArchivo(nombreArchivo);
    for (const auto &secuencia : secuencias) {
      auto start = std::chrono::steady_clock::now();
      int pos = buscaSecuencia(contenidoTransmision, secuencia);
      auto end = std::chrono::steady_clock::now();
      std::chrono::duration<double, std::milli> elapsed_seconds = end - start;
      if (pos != -1) {
        std::cout << "\n(true) Secuencia\n <<" << secuencia
                  << ">> encontrada en el archivo: \n"
                  << nombreArchivo << " en la posicion: \n"
                  << pos << std::endl;
      } else {
        std::cout << "\n(false) Secuencia no encontrada" << std::endl;
      }
      std::cout << "Tiempo de ejecución: " << elapsed_seconds.count() << "ms"
                << std::endl;
    }
  }

  // busca palindromos
  std::cout << "\n////// Parte 2 //////" << std::endl;
  std::cout << "\nEncuentra palindromo más largo por Manacher ---> \n"
            << std::endl;
  for (const auto &nombreArchivo : nombresTransmision) {
    std::string contenidoTransmision = leerArchivo(nombreArchivo);
    auto start = std::chrono::steady_clock::now();
    int maxLen = encuentraPalindromoManacher(contenidoTransmision);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed_seconds = end - start;
    if (maxLen > 0) {
      std::cout << "\n(true) Palindromo de longitud: " << maxLen
                << " encontrado en el archivo: \n"
                << nombreArchivo << std::endl;
    } else {
      std::cout << "(false) Palindromo no encontrado" << std::endl;
    }
    std::cout << "Tiempo de ejecución: " << elapsed_seconds.count() << "ms"
              << std::endl;
  }

  std::cout << "\nEncuentra palindromo más largo por busqueda bruta ---> \n"
            << std::endl;
  for (const auto &nombreArchivo : nombresTransmision) {
    std::string contenidoTransmision = leerArchivo(nombreArchivo);
    auto start = std::chrono::steady_clock::now();
    int maxLen = encuentraPalindromoBruto(contenidoTransmision);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed_seconds = end - start;
    if (maxLen > 0) {
      std::cout << "\n(true) Palindromo de longitud: " << maxLen
                << " encontrado en el archivo: \n"
                << nombreArchivo << std::endl;
    } else {
      std::cout << "(false) Palindromo no encontrado" << std::endl;
    }
    std::cout << "Tiempo de ejecución: " << elapsed_seconds.count() << "ms"
              << std::endl;
  }

  // encuentra el substring mas largo comun entre dos archivos
  std::cout << "\n////// Parte 3 //////" << std::endl;
  for (const auto &nombreArchivo : nombresTransmision) {
    std::string contenidoTransmision = leerArchivo(nombreArchivo);
    auto start = std::chrono::steady_clock::now();
    int maxLen = encuentraSubMasLargo(contenidoTransmision);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed_seconds = end - start;
    if (maxLen > 0) {
      std::cout << "\n(true) Substring de longitud: " << maxLen
                << " encontrado entre los archivos: \n"
                << nombresTransmision[0] << " y " << nombresTransmision[1]
                << std::endl;
    } else {
      std::cout << "(false) Substring no encontrado" << std::endl;
    }
    std::cout << "Tiempo de ejecución: " << elapsed_seconds.count() << "ms"
              << std::endl;
  }

  return 0;
}
