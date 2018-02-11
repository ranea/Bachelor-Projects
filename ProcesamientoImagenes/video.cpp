/**
  * @file video.cpp
  * @brief Implementación del TDA Video
  *
  */

/* ___________________________________________________________________ */


template <class T>
Video<T>::Video()
   :nframes(0)
{}


/* ___________________________________________________________________ */

template <class T>
Video<T>::Video(const Video<T>& V)
   :lista_frames(V.lista_frames), nframes(V.num_fotogramas())
{}


/* ___________________________________________________________________ */

template <class T>
Video<T> & Video<T>::operator=(const Video<T> &V)
{
   if (this != &V)
   {
      lista_frames = V.lista_frames;
      nframes = V.nframes;    
   }
   return *this;

}

/* ___________________________________________________________________ */

template <class T>
Video<T>::~Video(){}


/* ___________________________________________________________________ */

template <class T>
int Video<T>::num_fotogramas() const
{
   return nframes;
}


/* ___________________________________________________________________ */

template <class T>
Imagen<T>& Video<T>::operator[](int i)
{
   iterator it = begin();

   std::advance(it.lista_it, i);

   return *it;
}


/* ___________________________________________________________________ */

template <class T>
const Imagen<T>& Video<T>::operator[](int i) const
{
   const_iterator it = begin();

   std::advance(it.lista_it, i);

   return *it;
}



/* ------------ class iterator / const_iterator -------------------------- */

   /* ___________________________________________________________________ */

   template <class T>
   Video<T>::iterator::iterator(){}
   template <class T>
   Video<T>::const_iterator::const_iterator(){}


   /* ___________________________________________________________________ */

   template <class T>
   Video<T>::iterator::iterator(const Video<T>::iterator& it)
      :lista_it(it.lista_it)
   {}
   template <class T>
   Video<T>::const_iterator::const_iterator(const Video<T>::const_iterator& it)
      :lista_it(it.lista_it)
   {}


   /* ___________________________________________________________________ */

   template <class T>
   typename Video<T>::iterator& Video<T>::iterator::operator++()
   {
      lista_it++;
      return *this;
   }
   template <class T>
   typename Video<T>::const_iterator& Video<T>::const_iterator::operator++()
   {
      lista_it++;
      return *this;
   }


   /* ___________________________________________________________________ */

   template <class T>
   typename Video<T>::iterator& Video<T>::iterator::operator--()
   {
      lista_it--;
      return *this;
   }
   template <class T>
   typename Video<T>::const_iterator& Video<T>::const_iterator::operator--()
   {
      lista_it--;
      return *this;
   }

   /* ___________________________________________________________________ */

   template <class T>
   bool Video<T>::iterator::operator==(const Video<T>::iterator& it) const
   {
      return lista_it == it.lista_it;
   }
   template <class T>
   bool Video<T>::const_iterator::operator==(const Video<T>::const_iterator& it) const
   {
      return lista_it == it.lista_it;
   }


   /* ___________________________________________________________________ */

   template <class T>
   bool Video<T>::iterator::operator!=(const Video<T>::iterator& it) const
   {
      return lista_it != it.lista_it;
   }
   template <class T>
   bool Video<T>::const_iterator::operator!=(const Video<T>::const_iterator& it) const
   {
      return lista_it != it.lista_it;
   }


   /* ___________________________________________________________________ */

   template <class T>
   Imagen<T>& Video<T>::iterator::operator*()
   {
      return *lista_it;
   }
   template <class T>
   const Imagen<T>& Video<T>::const_iterator::operator*() const
   {
      return *lista_it;
   }

/* ___________________________________________________________________ */

template <class T>
typename Video<T>::iterator Video<T>::Insertar
   (Video<T>::iterator it, const Imagen<T> &I)
{
   iterator new_it;

   new_it.lista_it = lista_frames.insert(it.lista_it,I);
   nframes++;

   return new_it;
}


/* ___________________________________________________________________ */

template <class T>
typename Video<T>::iterator Video<T>::Borrar(Video<T>::iterator it)
{
   iterator new_it;

   new_it.lista_it = lista_frames.erase(it.lista_it);
   nframes--;
   return new_it;
}


/* ___________________________________________________________________ */

template <class T>
typename Video<T>::iterator Video<T>::begin()
{
   iterator it;
   it.lista_it = lista_frames.begin();
   return it;
}
template <class T>
typename Video<T>::const_iterator Video<T>::begin() const
{
   const_iterator it;
   it.lista_it = lista_frames.begin();
   return it;
}

/* ___________________________________________________________________ */

template <class T>
typename Video<T>::iterator Video<T>::end()
{
   iterator it;
   it.lista_it = lista_frames.end();
   return it;
}
template <class T>
typename Video<T>::const_iterator Video<T>::end() const
{
   const_iterator it;
   it.lista_it = lista_frames.end();
   return it;
}