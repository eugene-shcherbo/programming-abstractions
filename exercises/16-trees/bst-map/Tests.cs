using System.Collections.Generic;
using System.Linq;
using Xunit;

public class Tests
{
    [Fact]
    public void PutTests()
    {
        var map = new BstMap<int, int>();
        var elements = new[] { 43, 18, 22, 9, 21, 6, 8, 20, 63, 50, 62, 51 };

        foreach (var element in elements)
        {
            map.Put(element, element);
        }

        foreach (var elelement in elements)
        {
            Assert.Equal(elelement, map.Get(elelement));
        }
    }

    [Theory]
    [InlineData(10)]
    [InlineData(100)]
    [InlineData(5000)]
    [InlineData(50000)]
    [InlineData(100000)]
    [InlineData(500000)]
    public void DegenerateCase(int numOfElements)
    {
        var map = new BstMap<int, int>();
        var elementsToAdd = Enumerable.Range(0, numOfElements);

        foreach (var element in elementsToAdd)
        {
            map.Put(element, element);
        }

        foreach (var element in elementsToAdd)
        {
            Assert.Equal(element, map.Get(element));
        }
    }
}