#include "Presenter.hpp"



Presenter::Presenter():
    n_E_like_keys(default_n_E_like_keys),
    E_like_scancodes(default_E_like_scancodes),
    E_like_names(default_E_like_names)
{
    available_interactables = new Interactable*[n_E_like_keys];
    for (int i=0; i<n_E_like_keys; ++i)
        available_interactables[i] = nullptr;
}