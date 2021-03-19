void Visita-preorder-iter() 
{
    stack st;
    node *curr = radice;
    while(!st.pilavuota() || curr) 
	{
        if(curr) 
		{ 
		    cout<<curr->val;
            st.push(curr);
            curr = curr->sx
        }      
        else  
        {
            curr = st.primoelemento();
            st.pop();
            curr = curr->dx;
        }
    }
} 





void Visita-postorder-iter() 
{
    stack st;
    node *last, curr = radice;
    while(!st.pilavuota() || curr) 
	{
        if(curr) 
		{
            st.push(curr);
            curr = curr->sx
        }
        else 
	    { 
            curr = st.primoelemento();
            if (!curr->dx || last == curr->dx)
		    {
                cout<<curr->val<<" "; //Visita(curr);
                last = curr;
                st.pop();
                curr = NULL;
            }
            else curr = curr->dx; /* Discesa a dx */
        }
    }
} 


Inorder_Iterativa()   // sottoalbero sx -> radice -> sottoalbero dx 
{

    Pila stack; //pila vuota
    Nodo* current = radice; //si parte dalla radice
  
    bool done = false; //variabile che ci segnala se abbiamo finito
    while (!done) 
	{
        if (current)  //se current non è null procediamo verso sinistra , inserendo nel frattempo il nodo nella pila
	    {
            stack.Push(current);
            current = current->left; //andiamo verso sinistra
        } 
        else if (stack.PilaVuota()) //se la pila arriva a svuotarsi, abbiamo finito
            done = true;
        else 
	    {
            current = stack.Pop();  //siamo arrivati qua se current è nulla e la pila non è vuota
            cout << current->val << "\t"; //stampa elemento prelevato
            current = current->right; //procediamo verso destra
	    }
    }
}

