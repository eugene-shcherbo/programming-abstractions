using System;
using System.Collections;
using System.Collections.Generic;

public class FindDuplicateAlgorithm
{
    // The method assumes that each element of the IList
    // in the range [1, n - 1], where n is number of elements
    // in the IList
    public static int FindDuplicate(IList<int> values)
    {
        int duplicate = FindDuplicateElementIfAny(values);
        RestoreSequence(values);
        return duplicate;
    }

    private static int FindDuplicateElementIfAny(IList<int> values)
    {
        for (int i = 0; i < values.Count; i++)
        {
            int element = Math.Abs(values[i]);

            if (element >= values.Count)
            {
                throw new ArgumentException("Sequence is not in the correct format.");
            }
            else if (values[element] < 0)
            {
                return element;
            }
            else
            {
                values[element] *= -1;
            }
        }

        // Sequence is empty. If it weren't empty, we would be able to either find
        // a duplicate or detect that the sequence is not in the correct format.

        throw new ArgumentException("Sequence is not in the correct format.");
    }

    private static void RestoreSequence(IList<int> values)
    {
        for (int i = 0; i < values.Count; i++)
        {
            values[i] = Math.Abs(values[i]);
        }
    }
}