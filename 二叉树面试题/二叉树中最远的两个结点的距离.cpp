 size_t _GetMaxDistance(Node* root,size_t& distance)
    {
       if(root == NULL)
           return 0;
       int left = _GetMaxDistance(root->_left,distance);
       int right = _GetMaxDistance(root->_right,distance);
       if(left + right > distance)
           distance = left + right;
       return left > right ? left + 1: right + 1;
    }
