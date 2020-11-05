using System;
using System.Collections.Generic;
using System.Text;

public class BstMap<TKey, TValue> where TKey : notnull
{
    private BSTNode? root;

    public TValue Get(TKey key)
    {
        BSTNode? node = FindNode(ref root, key);

        if (node is null)
        {
            throw new KeyNotFoundException(key.ToString());
        }

        return node.value;
    }

    public void Put(TKey key, TValue value)
    {
        IComparer<TKey> comparer = GetComparer();
        PutInternal(ref root, key, value, comparer);
    }

    public override string ToString()
    {
        StringBuilder str = new StringBuilder();
        BuildStringRepresentation(root, str, 1);
        return str.ToString();
    }

    private IComparer<TKey> GetComparer()
    {
        if (typeof(TKey) == typeof(string))
        {
            return (IComparer<TKey>)StringComparer.OrdinalIgnoreCase;
        }
        return Comparer<TKey>.Default;
    }

    private void BuildStringRepresentation(BSTNode? root, StringBuilder builder, int spaces)
    {
        if (root == null)
        {
            return;
        }

        BuildStringRepresentation(root.right, builder, spaces + 5);
        builder.Append(' ', spaces);
        builder.Append(root.key);
        builder.Append(Environment.NewLine);
        BuildStringRepresentation(root.left, builder, spaces + 5);
    }

    private bool PutInternal(ref BSTNode? root, TKey key, TValue value, IComparer<TKey> comparer)
    {
        if (root == null)
        {
            // changes height of the root
            root = new BSTNode(key, value);
            return true;
        }
        else if (root.key.Equals(key))
        {
            // doesn't change height of the root
            root.value = value;
            return false;
        }
        else if (comparer.Compare(root.key, key) == 1)
        {
            return InsertToLeftSubtree(ref root, key, value, comparer);
        }
        else
        {
            return InsertToRightSubtree(ref root, key, value, comparer);
        }
    }

    private bool InsertToLeftSubtree(ref BSTNode root, TKey key, TValue value, IComparer<TKey> comparer)
    {
        bool bfChanged = PutInternal(ref root.left, key, value, comparer);

        if (!bfChanged)
        {
            return false;
        }

        switch (root.balanceFactor)
        {
            case -1:
                FixLeftImbalance(ref root);
                root.balanceFactor = 0;
                return false;
            case 0:
                root.balanceFactor = -1;
                return true;
            case 1:
                root.balanceFactor--;
                return false;
            default:
                throw new NotSupportedException();
        }
    }

    private bool InsertToRightSubtree(ref BSTNode root, TKey key, TValue value, IComparer<TKey> comparer)
    {
        bool bfChanged = PutInternal(ref root.right, key, value, comparer);

        if (!bfChanged)
        {
            return false;
        }

        switch (root.balanceFactor)
        {
            case -1:
                root.balanceFactor = 0;
                return false;
            case 0:
                root.balanceFactor = 1;
                return true;
            case 1:
                FixRightImbalance(ref root);
                root.balanceFactor = 0;
                return false;
            default:
                throw new NotSupportedException();
        }
    }

    private void FixRightImbalance(ref BSTNode node)
    {
        // Imbalance in left subtree
        if (node.right!.balanceFactor == -1)
        {
            RightLeftRotate(ref node);
        }
        else
        {
            LeftRotate(ref node);
            node.balanceFactor = 0;
            // There was one extra element in right subtree which goes to the left subtree
            node.left!.balanceFactor = 0;
        }
    }

    private void FixLeftImbalance(ref BSTNode node)
    {
        // Imbalance in right subtree
        if (node.left!.balanceFactor == 1)
        {
            LeftRightRotate(ref node);
        }
        else
        {
            RightRotate(ref node);
            node.balanceFactor = 0;
            // There was one extra element in left subtree which goes to the left subtree
            node.right!.balanceFactor = 0;
        }
    }

    private void RightLeftRotate(ref BSTNode node)
    {
        // We sure know that left is not null, because left subtree causes imbalance
        int oldBalanceFactor = node.right!.left!.balanceFactor;
        RightRotate(ref node.right!);
        LeftRotate(ref node);

        switch (oldBalanceFactor)
        {
            // left child goes to left subtree of node after left rotation
            // so new left subtree is missing one element
            case -1:
                node.left!.balanceFactor = 0;
                node.right!.balanceFactor = 1;
                break;
            case 0:
                node.left!.balanceFactor = 0;
                node.right!.balanceFactor = 0;
                break;
            // right child stays in the right subtree of the root
            // so new left subtree is missing one element
            case 1:
                node.left!.balanceFactor = -1;
                node.right!.balanceFactor = 0;
                break;
        }
    }

    private void LeftRightRotate(ref BSTNode node)
    {
        // We sure know that right is not null, because right subtree causes imbalance
        int oldBalanceFactor = node.left!.right!.balanceFactor;
        LeftRotate(ref node.left!);
        RightRotate(ref node);

        switch (oldBalanceFactor)
        {
            // left child goes to left subtree of node after left rotation
            // so new left subtree is missing one element
            case -1:
                node.right!.balanceFactor = 1;
                node.left!.balanceFactor = 0;
                break;
            case 0:
                node.left!.balanceFactor = 0;
                node.right!.balanceFactor = 0;
                break;
            // right child stays in the right subtree of the root
            // so new left subtree is missing one element
            case 1:
                node.right!.balanceFactor = 0;
                node.left!.balanceFactor = -1;
                break;
        }
    }

    private void LeftRotate(ref BSTNode node)
    {
        BSTNode right = node.right!;
        node.right = right.left;
        right.left = node;
        node = right;
    }

    private void RightRotate(ref BSTNode node)
    {
        BSTNode left = node.left!;
        node.left = left.right;
        left.right = node;
        node = left;
    }

    private ref BSTNode? FindNode(ref BSTNode? root, TKey key)
    {
        Comparer<TKey> comparer = Comparer<TKey>.Default;

        if (root is null)
        {
            return ref root;
        }
        else if (root.key.Equals(key))
        {
            return ref root;
        }
        else if (comparer.Compare(root.key, key) == 1)
        {
            return ref FindNode(ref root.left, key);
        }
        else
        {
            return ref FindNode(ref root.right, key);
        }
    }

    private class BSTNode
    {
        public TKey key;
        public TValue value;
        public BSTNode? left;
        public BSTNode? right;
        public int balanceFactor = 0;

        public BSTNode(TKey key, TValue value)
        {
            this.key = key;
            this.value = value;
        }
    }
}