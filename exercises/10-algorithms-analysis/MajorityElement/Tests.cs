using System;
using System.Linq;
using Xunit;

namespace MajorityElement
{
    public class Tests
    {
        [Fact]
        public void NoMajorityElementsInEmptyArray()
        {
            Assert.Equal(-1, MajorityElementAlgorithm.FindMajorityElement(Array.Empty<int>()));
        }

        [Fact]
        public void FindMajorityElement()
        {
            Assert.Equal(2, MajorityElementAlgorithm.FindMajorityElement(new[] { 1, 2, 1, 2, 2, 2, 3, 2 }));
        }

        [Fact]
        public void NoMajorityElementIfFiftyPercentOccurence()
        {
            Assert.Equal(-1, MajorityElementAlgorithm.FindMajorityElement(new[] { 1, 3, 1, 2, 2, 2, 3, 2 }));
        }
    }
}
