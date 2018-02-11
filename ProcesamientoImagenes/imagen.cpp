
template <class T>
Imagen<T>::Imagen()
{
   filas = 0;
   cols = 0;
   img = 0;
}   

template <class T>
Imagen<T>::Imagen(int filas, int columnas)
{
   this->filas = filas;
   cols = columnas;

   img = new T* [filas];

   img[0] = new T[filas*cols];
   for (int i = 1; i < filas; i++)
      img[i] = img[i-1]+cols;
}

template <class T>
Imagen<T>::Imagen(const Imagen &orig)
{
   this->filas = orig.filas;
   cols = orig.cols;

   img = new T* [filas];

   img[0] = new T[filas*cols];
   for (int i = 1; i < filas; i++)
      img[i] = img[i-1]+cols;

   for (int i = 0; i < filas; i++)
      for (int j = 0; j < cols; j++)
         this->img[i][j] = orig.img[i][j];
}

template <class T>
Imagen<T>::~Imagen()
{
   delete[] img[0];
   delete[] img;
}

template <class T>
int Imagen<T>::num_filas() const
{
   return filas;
}

template <class T>
int Imagen<T>::num_columnas() const
{
   return cols;
}

template <class T>
T & Imagen<T>::operator()(int fila, int col)
{
   return img[fila][col];
}

template <class T>
const T & Imagen<T>::operator()(int fila, int col) const
{
   return img[fila][col];
}

template <class T>
Imagen<T>& Imagen<T>::operator=(const Imagen<T> &orig)
{
   if (this != &orig)
   {
      filas = orig.filas;
      cols = orig.cols;

      img = new T* [filas];

      img[0] = new T[filas*cols];
      for (int i = 1; i < filas; i++)
         img[i] = img[i-1]+cols;

      for (int i = 0; i < filas; i++)
         for (int j = 0; j < cols; j++)
            this->img[i][j] = orig.img[i][j];
   }

   return *this;
}

template <class T>
bool Imagen<T>::es_vacia() const
{
   return (filas == 0 || cols == 0 || img == 0);
}

template <class T>
void Imagen<T>::rellena(const T* array)
{
   for (int i = 0; i < filas*cols; i++)
      img[0][i] = array[i];
}

template <class T>
void Imagen<T>::imprime(T* array) const
{
   for (int i = 0; i < filas*cols; i++)
      array[i] = img[0][i];
}



/* ---------------------- Iteradorres fila ------------------ */
   template <class T>
   Imagen<T>::iterator_fila::iterator_fila(int filas, int cols)
   {
      puntero = 0;
      this->filas = filas;
      this->cols = cols;
   }
   template <class T>
   Imagen<T>::const_iterator_fila::const_iterator_fila(int filas, int cols)
   {
      puntero = 0;
      this->filas = filas;
      this->cols = cols;
   }

   template <class T>
   Imagen<T>::iterator_fila::iterator_fila(const Imagen<T>::iterator_fila &it)
   {
      puntero = it.puntero;
      filas = it.filas;
      cols = it.cols;
   }
   template <class T>
   Imagen<T>::const_iterator_fila::const_iterator_fila
      (const Imagen<T>::const_iterator_fila &it)
   {
      puntero = it.puntero;
      filas = it.filas;
      cols = it.cols;
   }

   template <class T>
   typename Imagen<T>::iterator_fila& Imagen<T>::iterator_fila::operator= 
      (const Imagen<T>::iterator_fila& orig)
   {
      puntero = orig.puntero;
      filas = orig.filas;
      cols = orig.cols;
      return *this;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila& Imagen<T>::const_iterator_fila::operator= 
      (const Imagen<T>::const_iterator_fila& orig)
   {
      puntero = orig.puntero;
      filas = orig.filas;
      cols = orig.cols;
      return *this;
   }

   template <class T>
   T& Imagen<T>::iterator_fila::operator*() const
   {
      return *puntero;
   }
   template <class T>
   const T& Imagen<T>::const_iterator_fila::operator*() const
   {
      return *puntero;
   }

   template <class T>
   typename Imagen<T>::iterator_fila& Imagen<T>::iterator_fila::operator++()
   {
      puntero += filas;
      return *this;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila& Imagen<T>::const_iterator_fila::operator++()
   {
      puntero += filas;
      return *this;
   }

   template <class T>
   typename Imagen<T>::iterator_fila& Imagen<T>::iterator_fila::operator--()
   {
      puntero += filas;
      return *this;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila& Imagen<T>::const_iterator_fila::operator--()
   {
      puntero += filas;
      return *this;
   }

   template <class T>
   bool Imagen<T>::iterator_fila::operator!=(const Imagen<T>::iterator_fila& it) const
   {
      return puntero != it.puntero;
   }

   template <class T>
   bool Imagen<T>::const_iterator_fila::operator!=
      (const Imagen<T>::const_iterator_fila& it) const
   {
      return puntero != it.puntero;
   }

   template <class T>
   bool Imagen<T>::iterator_fila::operator==(const Imagen<T>::iterator_fila& it) const
   {
      return puntero == it.puntero;
   }
   template <class T>
   bool Imagen<T>::const_iterator_fila::operator==
      (const Imagen<T>::const_iterator_fila& it) const
   {
      return puntero == it.puntero;
   }

   template <class T>
   typename Imagen<T>::iterator_fila::iterator_columna Imagen<T>::iterator_fila::begin()
   {
      iterator_columna it;
      it.puntero = &puntero[0];
      return it;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila::const_iterator_columna 
   Imagen<T>::const_iterator_fila::begin() const
   {
      const_iterator_columna it;
      it.puntero = &puntero[0];
      return it;
   }

   template <class T>
   typename Imagen<T>::iterator_fila::iterator_columna Imagen<T>::iterator_fila::end()
   {
      iterator_columna it;
      it.puntero = &puntero[cols];
      return it;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila::const_iterator_columna 
   Imagen<T>::const_iterator_fila::end() const
   {
      const_iterator_columna it;
      it.puntero = &puntero[cols];
      return it;
   }


/* ---------------------- Iterator_columna ------------------ */
   template <class T>
   Imagen<T>::iterator_fila::iterator_columna::iterator_columna()
   {
      puntero = 0;
   }
   template <class T>
   Imagen<T>::const_iterator_fila::const_iterator_columna::const_iterator_columna()
   {
      puntero = 0;
   }

   template <class T>
   Imagen<T>::iterator_fila::iterator_columna::iterator_columna
      (const Imagen<T>::iterator_fila::iterator_columna &it)
   {
      puntero = it.puntero;
   }
   template <class T>
   Imagen<T>::const_iterator_fila::const_iterator_columna::const_iterator_columna
      (const Imagen<T>::const_iterator_fila::const_iterator_columna &it)
   {
      puntero = it.puntero;
   }

   template <class T>
   typename Imagen<T>::iterator_fila::iterator_columna& 
   Imagen<T>::iterator_fila::iterator_columna::operator=
      (const Imagen<T>::iterator_fila::iterator_columna& orig)
   {
      puntero = orig.puntero;
      return *this;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila::const_iterator_columna& 
   Imagen<T>::const_iterator_fila::const_iterator_columna::operator=
      (const Imagen<T>::const_iterator_fila::const_iterator_columna& orig)
   {
      puntero = orig.puntero;
      return *this;
   }

   template <class T>
   T& Imagen<T>::iterator_fila::iterator_columna::operator*() const
   {
      return *puntero;
   }
   template <class T>
   const T& Imagen<T>::const_iterator_fila::const_iterator_columna::operator*() const
   {
      return *puntero;
   }

   template <class T>
   typename Imagen<T>::iterator_fila::iterator_columna& 
   Imagen<T>::iterator_fila::iterator_columna::operator++()
   {
      puntero++;
      return *this;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila::const_iterator_columna& 
      Imagen<T>::const_iterator_fila::const_iterator_columna::operator++()
   {
      puntero++;
      return *this;
   }

   template <class T>
   typename Imagen<T>::iterator_fila::iterator_columna& 
   Imagen<T>::iterator_fila::iterator_columna::operator--()
   {
      puntero--;
      return *this;
   }
   template <class T>
   typename Imagen<T>::const_iterator_fila::const_iterator_columna& 
      Imagen<T>::const_iterator_fila::const_iterator_columna::operator--()
   {
      puntero--;
      return *this;
   }

   template <class T>
   bool Imagen<T>::iterator_fila::iterator_columna::operator!=
      (const Imagen<T>::iterator_fila::iterator_columna& it) const
   {
      return puntero != it.puntero;
   }
   template <class T>
   bool Imagen<T>::const_iterator_fila::const_iterator_columna::operator!=
      (const Imagen<T>::const_iterator_fila::const_iterator_columna& it) const
   {
      return puntero != it.puntero;
   }

   template <class T>
   bool Imagen<T>::iterator_fila::iterator_columna::operator==
      (const Imagen<T>::iterator_fila::iterator_columna& it) const
   {
      return puntero == it.puntero;
   }
   template <class T>
   bool Imagen<T>::const_iterator_fila::const_iterator_columna::operator==
      (const Imagen<T>::const_iterator_fila::const_iterator_columna& it) const
   {
      return puntero == it.puntero;
   }


/* ------------ Fin iteradores ------------------ */

template <class T>
typename Imagen<T>::iterator_fila Imagen<T>::begin()
{
   iterator_fila it(filas,cols);
   it.puntero = img[0];
   return it;
}


template <class T>
typename Imagen<T>::const_iterator_fila Imagen<T>::begin() const
{
   const_iterator_fila it(filas,cols);
   it.puntero = img[0];
   return it;
}

template <class T>
typename Imagen<T>::iterator_fila Imagen<T>::end()
{
   iterator_fila it(filas,cols);
   it.puntero = img[filas-1];
   return it;
}

template <class T>
typename Imagen<T>::const_iterator_fila Imagen<T>::end() const
{
   const_iterator_fila it(filas,cols);
   it.puntero = img[filas-1];
   return it;
}