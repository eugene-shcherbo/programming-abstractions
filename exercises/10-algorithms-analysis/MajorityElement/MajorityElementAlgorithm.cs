using System.Collections.Generic;
using System.Linq;

public class MajorityElementAlgorithm
{
    private const int NoMajorityElement = -1;

    public static int FindMajorityElement(IList<int> values)
    {
        if (!values.Any())
        {
            return NoMajorityElement;
        }

        int candidate = FindCandidate(values);
        int howMany = CountOccurence(values, candidate);

        return howMany > (values.Count / 2) ? candidate : NoMajorityElement;
    }

    private static int FindCandidate(IList<int> values)
    {
        int candidatePos = 0;
        int voting = 1;

        for (int i = 1; i < values.Count; i++)
        {
            voting += (values[i] == values[candidatePos] ? 1 : -1);

            if (voting == 0)
            {
                candidatePos = i;
            }
        }

        return values[candidatePos];
    }

    private static int CountOccurence(IList<int> values, int value)
    {
        int count = 0;

        for (int i = 0; i < values.Count; i++)
        {
            if (values[i] == value)
            {
                count++;
            }
        }

        return count;
    }

}
